#include <stdint.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <immintrin.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include "libxom.h"
#include "modxom.h"

#define TEXT_TYPE_EXECUTABLE    1
#define TEXT_TYPE_LIBC          2
#define TEXT_TYPE_SHARED        3

#define PAGE_SIZE   0x1000
#define PAGE_SHIFT  12

#define MAX_ORDER 11
#define ALLOC_CHUNK_SIZE ((1 << (MAX_ORDER - 1)) << PAGE_SHIFT)

#define SIZE_CEIL(S)    ((((S) >> PAGE_SHIFT) + ((S) & (PAGE_SIZE - 1) ? 1 : 0) ) << PAGE_SHIFT)
#define min(x, y)       ((x) < (y) ? (x) : (y))

extern char **__environ;

struct xombuf {
    void* address;
    size_t allocated_size;
    uint8_t locked;
} __attribute__((packed)) typedef _xombuf, *p_xombuf;

struct xom_subpages{
    void* address;
    size_t num_subpages;
    int8_t references;
    uint32_t* lock_status;
} typedef _xom_subpages, *p_xom_subpages;


// Describes an executable memory region
struct {
    char* text_base;                  // Start of memory region, must be page-aligned
    char* text_end;                   // End of memory region, must be page-aligned
    unsigned char type;               // Type of memory region (main executable, shared library or libc)
    unsigned char jump_into_backup;   // Do we have to jump into backup code when unmapping this region?
} typedef text_region;


static volatile uint8_t initialized = 0;
static pthread_mutex_t lib_lock;
static int32_t xomfd = -1;
static void* xom_base_addr = NULL;

#define wrap_call(T, F) {           \
    T r;                            \
    __libxom_prologue();            \
    r = F;                          \
    __libxom_epilogue();            \
    return r;                       \
}

static text_region* explore_text_regions();

static inline void __libxom_prologue(){
    pthread_mutex_lock(&lib_lock);
}

static inline void __libxom_epilogue(){
    pthread_mutex_unlock(&lib_lock);
}

/**
 * Parse the /proc/<pid>/maps file to find all executable memory segments
 * 
 * @returns An array of text_region structs, which is terminated by an
 *  entry with .type = 0. The caller must free this array
*/
static text_region* explore_text_regions(){
    char mpath[64] = {0, };
    char perms[3] = {0, };
    char *line = NULL;
    int status, is_libc;
    size_t start, end, last = 0, len = 0;
    ssize_t res, count = 0;
    FILE* maps;
    text_region* regions;

    snprintf(mpath, sizeof(mpath), "/proc/%u/maps", (unsigned int) getpid());
    maps = fopen(mpath, "r");
    if(!maps)
        return NULL;
    
    // Get amount of executable memory regions
    while ((res = getline(&line, &len, maps)) != -1) {
        status = sscanf(line, "%lx-%lx %c%c%c", &start, &end, &perms[0], &perms[1], &perms[2]);
        free(line);
        line = NULL;
        if(status != 5)
            continue;
        count += perms[2] == 'x' ? 1 : 0;
    }
    rewind(maps);

    // We need this buffer until it was used once, which may be never
    regions = malloc(sizeof(*regions) * (count + 1));
    if(!regions)
        return NULL;

    count = 0;
    while ((res = getline(&line, &len, maps)) != -1) {
        status = sscanf(line, "%lx-%lx %c%c%c", &start, &end, &perms[0], &perms[1], &perms[2]);
        is_libc = strstr(line, "libc.so") ? 1 : 0;
        free(line);
        line = NULL;
        if(status != 5)
            continue;
        if(perms[2] != 'x')
            continue;
        
        regions[count].text_base = (char*) start;
        regions[count].text_end = (char*) end;

        if (!count)
            regions[count].type = TEXT_TYPE_EXECUTABLE;
        else if (is_libc)
            regions[count].type = TEXT_TYPE_LIBC;
        else
            regions[count].type = TEXT_TYPE_SHARED;
        
        regions[count].jump_into_backup = (start <= (size_t)explore_text_regions && 
                end > (size_t)explore_text_regions) ? 1 : 0;
        count++;
    }
    fclose(maps);

    regions[count].type = 0;

    return regions;
}

/**
 * Unmap the code specified by space, remap it as xom, and fill it with the data in dest
 * 
 * @param space A text_region describing the code section that should be remapped
 * @param dest A backup buffer containing the code in space. It must have the same size
 * @param fd The /proc/xom file descriptor
 * 
 * @returns 0 upon success, a negative value otherwise
*/
static int remap_no_libc(text_region* space, char* dest, int32_t fd){
    int status;
    unsigned int i, c = 0;
    char *remapping = space->text_base;
    ssize_t size_left = space->text_end - space->text_base;

    /*
    remap_no_libc must work in an environment where the GOT is unavailable,
    which means that we cannot use any shared libraries whatsoever.
    This unfortunately includes libc, so we have to inline absolutely
    everything, including syscalls and memcpy
    */

    // Munmap old .text section
    asm volatile("syscall" : "=a"(status) : "a"(SYS_munmap), 
        "D"(space->text_base), "S"(space->text_end - space->text_base));

    // If there is an error, we can do nothing but quit
    if(status < 0)
        asm volatile("syscall" :: "a"(SYS_exit), "D"(1));  // exit(1)

    //ret->address = mmap(NULL, SIZE_CEIL(size), PROT_READ | PROT_WRITE, MAP_PRIVATE, xomfd, 0);
    // Mmap new .text section
    while(size_left > 0){
        asm volatile(
            "mov %%ecx, %%ecx\n"
            "mov %%rcx, %%r10\n"
            "mov %%ebx, %%ebx\n"
            "mov %%rbx, %%r8\n"
            "mov $0, %%r9\n"
            "syscall\n"
            "mov %%rax, %0"
            : "=r" (remapping) 
            : "a"(SYS_mmap), "D"(remapping), "S"(min(size_left, ALLOC_CHUNK_SIZE)), 
                "d"(PROT_READ | PROT_WRITE), "c"(MAP_PRIVATE), "b"(fd)
            : "r8", "r9", "r10"
        );

        if(remapping != space->text_base + c * ALLOC_CHUNK_SIZE)
            asm volatile("syscall" :: "a"(SYS_exit), "D"(remapping)); // exit(1)
        
        remapping += ALLOC_CHUNK_SIZE;
        size_left -= ALLOC_CHUNK_SIZE;
        c++;
    }

    // Copy from backup into new .txt
    for(i = 0; i < (space->text_end - space->text_base) / sizeof(size_t); i++)
        ((size_t*) space->text_base)[i] = ((size_t*) (dest))[i];

    // Make new code executable
    // asm volatile ("syscall" :: "a"(SYS_mprotect), "D"(space->text_base), 
    //    "S"(space->text_end - space->text_base), "d"(PROT_EXEC | PROT_READ));

    return 0;
}

/**
 * Migrate the code in space to XOM
 * 
 * @param space A text_region describing the code that should be migrated
 * @returns 0 upon success, a negative value otherwise
*/
static int migrate_text_section(text_region* space){
    int status;
    unsigned int i, c = 0;
    char* dest;
    size_t num_pages = (space->text_end - space->text_base) >> PAGE_SHIFT;
    ssize_t size_left;
    int (*remap_function)(text_region*, char*, int32_t);
    modxom_cmd cmd;

    //printf("Remapping %p - %p, type %u - %u\n", space->text_base, space->text_end, space->type, space->jump_into_backup);

    // Mmap code backup
    dest = mmap(NULL, num_pages << PAGE_SHIFT, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if(!~(uintptr_t)dest)
        return -1;
    
    // Copy code
    memcpy(dest, space->text_base, num_pages << PAGE_SHIFT);

    remap_function = remap_no_libc;

    // We cannot unmap the code we are currently executing. If this needs to be done, jump
    // into the backup and do it from there
    if(space->jump_into_backup){
        mprotect(dest, num_pages << PAGE_SHIFT, PROT_READ | PROT_EXEC);
        remap_function = (int(*)(text_region*, char*, int32_t)) ((size_t)remap_function + (ssize_t)(dest - space->text_base));
    }

    status = remap_function(space, dest, xomfd); 
    size_left = (space->text_end - space->text_base);
    while(status >= 0 && size_left > 0){
        cmd.cmd = MODXOM_CMD_LOCK;
        cmd.num_pages = min(size_left, ALLOC_CHUNK_SIZE) >> PAGE_SHIFT;
        cmd.base_addr = (uintptr_t) space->text_base + c * ALLOC_CHUNK_SIZE;
        status = write(xomfd, &cmd, sizeof(cmd));
        size_left -= ALLOC_CHUNK_SIZE;
        c++;
    }

    // Unmap backup
    munmap(dest, num_pages << PAGE_SHIFT);
    return status;
}

static int migrate_shared_libraries_internal(){
    int status = 1;
    unsigned int i = 0;
    text_region* spaces;

    if(xomfd < 0)
        return -1;

    spaces = explore_text_regions();
    if(!spaces)
        return -1;

    while(spaces[i].type){
        if(spaces[i].type == TEXT_TYPE_EXECUTABLE){
            i++;
            continue;
        }

        status = migrate_text_section(&(spaces[i]));
        if(status < 0)
            break;
        i++;
    }

    free(spaces);
    spaces = NULL;

    return status;
}


static int migrate_all_code_internal(){
    int status = 0;
    unsigned int i = 0;
    text_region* spaces;

    if(xomfd < 0)
        return -1;

    spaces = explore_text_regions();
    if(!spaces)
        return -1;

    while(spaces[i].type){
        status = migrate_text_section(&(spaces[i]));
        if(status < 0)
            break;
        i++;
    }

    free(spaces);
    spaces = NULL;

    return status;
}

static p_xombuf xomalloc_page_internal(size_t size){
    void* current_address = xom_base_addr, *last_address = NULL;
    ssize_t size_left = size;
    p_xombuf ret;
    
    if(!size){
        errno = EINVAL;
        return NULL;
    }
    
    ret = malloc(sizeof(*ret));

    if(!ret){
        errno = ENOMEM;
        return NULL;
    }

    ret->address = NULL;
    while(size_left > 0){
        current_address = mmap(current_address, SIZE_CEIL(min(ALLOC_CHUNK_SIZE, size_left)), PROT_READ | PROT_WRITE, MAP_PRIVATE, xomfd, 0);
        if(!current_address)
            goto fail;
        if(!ret->address)
            ret->address = current_address;
        last_address = current_address;
        current_address += ALLOC_CHUNK_SIZE;
        xom_base_addr = current_address;
        size_left -= ALLOC_CHUNK_SIZE;
    }
    
    ret->allocated_size = size;
    ret->locked = 0;
    return ret;

fail:
    size_left = size;
    while(ret->address && ret->address <= last_address){
        munmap(ret->address, SIZE_CEIL(min(ALLOC_CHUNK_SIZE, size_left)));
        ret->address += ALLOC_CHUNK_SIZE;
        size_left-= ALLOC_CHUNK_SIZE;
    }
    free(ret);
    return NULL;
}

static int xom_write_internal(struct xombuf* dest, const void *const src, const size_t size){
    if(!dest || !src || !size){
        errno = EINVAL;
        return -1;
    }
    if(dest->locked || dest->allocated_size < size){
        errno = EINVAL;
        return -1;
    }
    memcpy(dest->address, src, size);
    return (int) size;
}

static void* xom_lock_internal(struct xombuf* buf){
    int status, c = 0;
    modxom_cmd cmd;
    ssize_t size_left;
    
    if(!buf){
        errno = EINVAL;
        return NULL;
    }
    if(buf->locked)
        return buf->address;

    size_left = buf->allocated_size;
    while(size_left > 0){
        cmd = (modxom_cmd) {
            .cmd = MODXOM_CMD_LOCK,
            .num_pages = (uint32_t) SIZE_CEIL(min(size_left, ALLOC_CHUNK_SIZE)) >> PAGE_SHIFT,
            .base_addr = (uintptr_t) buf->address + c * ALLOC_CHUNK_SIZE
        };
        status = write(xomfd, &cmd, sizeof(cmd));
        if(status < 0)
            return NULL;
        size_left -= ALLOC_CHUNK_SIZE;
        c++;
    }
    buf->locked = 1;
    return buf->address;
}

static void xom_free_internal(struct xombuf* buf){
    unsigned int c = 0;
    modxom_cmd cmd;
    ssize_t size_left;
    
    if(!buf)
        return;
    
    size_left = buf->allocated_size;
    while(size_left > 0){
        cmd = (modxom_cmd) {
            .cmd = MODXOM_CMD_FREE,
            .num_pages = SIZE_CEIL(min(size_left, ALLOC_CHUNK_SIZE)) >> PAGE_SHIFT,
            .base_addr = (uintptr_t) buf->address + c * ALLOC_CHUNK_SIZE
        };
        write(xomfd, &cmd, sizeof(cmd));
        munmap(buf->address, SIZE_CEIL(min(size_left, ALLOC_CHUNK_SIZE)));
        size_left -= ALLOC_CHUNK_SIZE;
        c++;
    }
    free(buf);
}

struct xom_subpages* xom_alloc_subpages_internal(size_t size){
    int status;
    modxom_cmd cmd;
    p_xom_subpages ret = NULL;
    p_xombuf xombuf = xomalloc_page_internal(size);

    if(!xombuf)
        return NULL;
    
    if(size > ALLOC_CHUNK_SIZE)
        return NULL;
    
    cmd.cmd = MODXOM_CMD_INIT_SUBPAGES;
    cmd.base_addr = (uintptr_t) xombuf->address;
    cmd.num_pages = SIZE_CEIL(xombuf->allocated_size) >> PAGE_SHIFT;
    status = write(xomfd, &cmd, sizeof(cmd));
    if(status < 0)
        goto exit;
    
    ret = malloc(sizeof(*ret));
    if(!ret){
        errno = ENOMEM;
        goto exit;
    }

    *ret = (_xom_subpages){
        .address = xombuf->address,
        .lock_status = malloc(sizeof(uint32_t) * (SIZE_CEIL(size) >> PAGE_SHIFT)),
        .references = 0,
        .num_subpages = (size / SUBPAGE_SIZE) + (size % SUBPAGE_SIZE ? 1 : 0)
    };

    if(!ret->lock_status){
        free(ret);
        ret = NULL;
        errno = ENOMEM;
    } else {
        memset(ret->lock_status, 0, sizeof(uint32_t) * (SIZE_CEIL(size) >> PAGE_SHIFT));
    }

exit:
    free(xombuf);
    return ret;
}

void* xom_fill_and_lock_subpages_internal(struct xom_subpages* dest, size_t size, const void *const src){
    int status;
    size_t subpages_required = (size / SUBPAGE_SIZE) + (size % SUBPAGE_SIZE ? 1 : 0);
    uint32_t mask;
    xom_subpage_write* write_cmd;
    unsigned int base_page, base_subpage, i;

    if(!size || subpages_required > dest->num_subpages || subpages_required > MAX_SUBPAGES_PER_CMD){
        errno = EINVAL;
        return NULL;
    }
    
    
    mask = (uint32_t) ((1 << subpages_required) - 1);
    
    for(base_page = 0; base_page < (dest->num_subpages * SUBPAGE_SIZE) / PAGE_SIZE; base_page++){
        base_subpage = 0;
        while(base_subpage <= (PAGE_SIZE / SUBPAGE_SIZE) - subpages_required){
            if(!((mask << base_subpage) & dest->lock_status[base_page]))
                goto subpages_found;
            base_subpage++;
        } 
    }

    errno = -ENOMEM;
    return NULL;

subpages_found:
    write_cmd = malloc(sizeof(*write_cmd));

    write_cmd->mxom_cmd = (modxom_cmd) {
        .cmd = MODXOM_CMD_WRITE_SUBPAGES,
        .num_pages = 1,
        .base_addr = (uintptr_t) (dest->address + base_page * PAGE_SIZE),
    };

    write_cmd->xen_cmd.num_subpages = subpages_required;

    for(i = 0; i < subpages_required; i++){
        write_cmd->xen_cmd.write_info[i].target_subpage = i + base_subpage;
        memcpy(write_cmd->xen_cmd.write_info[i].data, (char*)src + (i*SUBPAGE_SIZE), SUBPAGE_SIZE);
    }

    status = write(xomfd, write_cmd, 
        sizeof(write_cmd->mxom_cmd) + sizeof(write_cmd->xen_cmd.num_subpages) + 
            subpages_required * sizeof(*write_cmd->xen_cmd.write_info));
    
    free(write_cmd);
    
    if(status < 0){
        status = -EINVAL;
        return NULL;
    }

    dest->lock_status[base_page] |= mask << base_subpage;
    dest->references++;
    return dest->address + base_page * PAGE_SIZE + base_subpage * SUBPAGE_SIZE;
}

void xom_free_all_subpages_internal(struct xom_subpages* subpages){
    p_xombuf xbuf = malloc(sizeof(*xbuf));

    if(xbuf){
        *xbuf = (_xombuf){
            .address = subpages->address,
            .allocated_size = subpages->num_subpages * SUBPAGE_SIZE,
            .locked = 1,
        };
        xom_free_internal(xbuf);
    }
    free(subpages);
}

static int xom_free_subpages_internal(struct xom_subpages* subpages, void* base_address){
    if (base_address < subpages->address)
        return -1;
    if(base_address >= subpages->address + (subpages->num_subpages * SUBPAGE_SIZE))
        return -1;
    
    subpages->references--;
    if(subpages->references <= 0){
        xom_free_all_subpages_internal(subpages);
        return 1;
    }
    return 0;
}

struct xombuf* xom_alloc_pages(size_t size){
    wrap_call(struct xombuf*, xomalloc_page_internal(size));
}

size_t xom_get_size(struct xombuf* buf){
    if(!buf)
        return 0;
    return buf->allocated_size;
}

int xom_write(struct xombuf* dest, const void *const src, const size_t size){
    wrap_call(int, xom_write_internal(dest, src, size));
}

void* xom_lock(struct xombuf* buf){
    wrap_call(void*, xom_lock_internal(buf));
}

void xom_free(struct xombuf* buf){
    __libxom_prologue();
    xom_free_internal(buf);
    __libxom_epilogue();    
}

int xom_migrate_all_code(){
    wrap_call(int, migrate_all_code_internal());
}

int xom_migrate_shared_libraries(){
    wrap_call(int, migrate_shared_libraries_internal());
}

struct xom_subpages* xom_alloc_subpages(size_t size){
    wrap_call(p_xom_subpages, xom_alloc_subpages_internal(size))
}

void* xom_fill_and_lock_subpages(struct xom_subpages* dest, size_t size, const void *const src){
    wrap_call(void*, xom_fill_and_lock_subpages_internal(dest, size, src))
}

int xom_free_subpages(struct xom_subpages* subpages, void* base_address){
    wrap_call(int, xom_free_subpages_internal(subpages, base_address))
}

void xom_free_all_subpages(struct xom_subpages* subpages){
    __libxom_prologue();
    xom_free_all_subpages_internal(subpages);
    __libxom_epilogue();   
}

__attribute__((constructor))
static void initialize_libxom() {
    char** envp = __environ;
    uintptr_t rval = 0;
    if(initialized)
        return;
    pthread_mutex_init(&lib_lock, NULL);
    initialized = 1;
    pthread_mutex_lock(&lib_lock);
    xomfd = open("/proc/xom", O_RDWR);
    while(*envp) {
        if(strstr(*envp, "LIBXOM_LOCK=all")){
            migrate_all_code_internal();
            break;
        }
        else if (strstr(*envp, "LIBXOM_LOCK=libs")){
            migrate_shared_libraries_internal();
            break;
        }
        envp++;
    }
    while(!rval)
        _rdrand32_step((uint32_t*)&rval);
    xom_base_addr = (void*) (0x420000000000 + ((rval << PAGE_SHIFT) & ~(0xff0000000000)));
    pthread_mutex_unlock(&lib_lock);
}

