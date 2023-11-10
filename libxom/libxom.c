#include <stdint.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include "libxom.h"
#include "modxom.h"

#define TEXT_TYPE_EXECUTABLE    1
#define TEXT_TYPE_LIBC          2
#define TEXT_TYPE_SHARED        3

#define PAGE_SIZE   0x1000
#define PAGE_SHIFT  12
#define SIZE_CEIL(S) ((((S) >> PAGE_SHIFT) + ((S) & (PAGE_SIZE - 1) ? 1 : 0) ) << PAGE_SHIFT)

struct xombuf {
    void* address;
    size_t allocated_size;
    uint8_t locked;
} __attribute__((packed)) typedef _xombuf, *p_xombuf;


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

#define wrap_call(T, F) {           \
    T r;                            \
    __libxom_prologue();            \
    r = F;                          \
    __libxom_epilogue();            \
    return r;                       \
}

static text_region* explore_text_regions();

static void __libxom_prologue(){
    unsigned i;
    if(initialized){
        while(initialized == 2);
        pthread_mutex_lock(&lib_lock);
        return;
    }
    initialized = 2;
    pthread_mutex_init(&lib_lock, NULL);
    initialized = 1;
    pthread_mutex_lock(&lib_lock);
    xomfd = open("/proc/xom", O_RDWR);
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
    char mpath[64] = {0};
    pid_t pid = getpid();
    char * line = NULL;
    size_t len = 0;
    FILE* maps;
    ssize_t res, count = 0;
    size_t start, end, last = 0;
    char perms[3];
    int status;
    text_region* regions;

    snprintf(mpath, sizeof(mpath), "/proc/%u/maps", (unsigned int) pid);
    maps = fopen(mpath, "r");
    if(!maps){
        printf("Failed to open, errno %d\n", errno);
        return NULL;
    }
    
    while ((res = getline(&line, &len, maps)) != -1) {
        status = sscanf(line, "%lx-%lx %c%c%c", &start, &end, &perms[0], &perms[1], &perms[2]);
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
        if(status != 5)
            continue;
        if(perms[2] != 'x')
            continue;
        
        regions[count].text_base = (char*) start;
        regions[count].text_end = (char*) end;

        if(!count)
            regions[count].type = TEXT_TYPE_EXECUTABLE;
        else if(strstr(line, "libc.so"))
            regions[count].type = TEXT_TYPE_LIBC;
        else
            regions[count].type = TEXT_TYPE_SHARED;
        
        regions[count].jump_into_backup = (start <= (size_t)explore_text_regions && end > (size_t)explore_text_regions) ? 1 : 0;
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
 * 
 * @returns 0 upon success, a negative value otherwise
*/
static int remap_no_libc(text_region* space, char* dest){
    int status;
    unsigned int i;
    char *remapping;

    /*
    remap_no_libc must work in an environment where the GOT is unavailable,
    which means that we cannot use any shared libraries whatsoever.
    This unfortunately includes libc, so we have to inline absolutely
    everything, including syscalls and memcpy
    */

    // Munmap old .text section
    asm volatile("syscall" : "=a"(status) : "a"(SYS_munmap), "D"(space->text_base), "S"(space->text_end - space->text_base));

    // If there is an error, we can do nothing but quit
    if(status < 0)
        asm volatile("syscall" :: "a"(SYS_exit), "D"(1));  // exit(1)
    
    // Mmap new .text section
    asm volatile(
        "mov %%ecx, %%ecx\n"
        "mov %%rcx, %%r10\n"
        "mov %%ebx, %%ebx\n"
        "mov %%rbx, %%r8\n"
        "mov $0, %%r9\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=r" (remapping) 
        : "a"(SYS_mmap), "D"(space->text_base), "S"(space->text_end - space->text_base), 
            "d"(PROT_READ | PROT_WRITE), "c"(MAP_ANONYMOUS | MAP_PRIVATE), "b"(xomfd)
        : "r8", "r9", "r10"
    );

    if(remapping != space->text_base)
        asm volatile("syscall" :: "a"(SYS_exit), "D"(errno)); // exit(1)

    // Copy from backup into new .txt
    for(i = 0; i < (space->text_end - space->text_base) / sizeof(size_t); i++)
        ((size_t*) space->text_base)[i] = ((size_t*) (dest))[i];

    // Make new code executable
    // asm volatile ("syscall" :: "a"(SYS_mprotect), "D"(space->text_base), "S"(space->text_end - space->text_base), "d"(PROT_EXEC | PROT_READ));

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
    unsigned int i;
    char* dest;
    size_t num_pages = (space->text_end - space->text_base) >> PAGE_SHIFT;
    int (*remap_function)(text_region*, char*);
    modxom_cmd cmd = {
        .cmd = MODXOM_CMD_LOCK,
        .num_pages = num_pages,
        .base_addr = (unsigned long) space->text_base,
    };

    // Mmap code backup
    dest = mmap(NULL, num_pages << PAGE_SHIFT, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if(!~(uintptr_t)dest) {
        printf("Mmap failed, errno %d\n", errno);
        return -1;
    }
    
    // Copy code
    memcpy(dest, space->text_base, num_pages << PAGE_SHIFT);

    remap_function = remap_no_libc;

    // We cannot unmap the code we are currently executing. If this needs to be done, jump
    // into the backup and do it from there
    if(space->jump_into_backup){
        mprotect(dest, num_pages << PAGE_SHIFT, PROT_READ | PROT_EXEC);
        remap_function = (int(*)(text_region*, char*)) ((uintptr_t)remap_function + (ssize_t)(dest - space->text_base));
    }

    status = remap_function(space, dest);
    if(!status)
        status = write(xomfd, &cmd, sizeof(cmd));

    // Unmap backup
    munmap(dest, num_pages << PAGE_SHIFT);
    return status;
}

static inline int migrate_shared_libraries_internal(){
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


static inline int migrate_all_code_internal(){
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

static inline p_xombuf xomalloc_internal(size_t size){
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

    ret->address = mmap(NULL, SIZE_CEIL(size), PROT_READ | PROT_WRITE, MAP_PRIVATE, xomfd, 0);
    if(!ret->address || !~(uintptr_t)ret->address)
        return NULL;
    
    ret->allocated_size = size;
    ret->locked = 0;
    return ret;
}

static inline int xom_write_internal(struct xombuf* dest, const void *const src, const size_t size){
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

static inline void* xom_lock_internal(struct xombuf* buf){
    int status;
    modxom_cmd cmd;
    
    if(!buf){
        errno = EINVAL;
        return NULL;
    }

    cmd = (modxom_cmd) {
        .cmd = MODXOM_CMD_LOCK,
        .num_pages = (uint32_t) SIZE_CEIL(buf->allocated_size) >> PAGE_SHIFT,
        .base_addr = (uintptr_t) buf->address
    };

    status = write(xomfd, &cmd, sizeof(cmd));
    if(status < 0)
        return NULL;
    buf->locked = 1;
    return buf->address;
}

static inline void xom_free_internal(struct xombuf* buf){
    uint32_t num_pages;
    modxom_cmd cmd;
    
    if(!buf)
        return;
    
    num_pages = (uint32_t) SIZE_CEIL(buf->allocated_size) >> PAGE_SHIFT;
    cmd = (modxom_cmd) {
        .cmd = MODXOM_CMD_FREE,
        .num_pages = num_pages,
        .base_addr = (uintptr_t) buf->address
    };
    write(xomfd, &cmd, sizeof(cmd));
    munmap(buf->address, num_pages << PAGE_SHIFT);
    free(buf);
}

struct xombuf* xom_alloc(size_t size){
    wrap_call(struct xombuf*, xomalloc_internal(size));
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
    if(initialized) 
        return -1;
    wrap_call(int, migrate_all_code_internal());
}

int xom_migrate_shared_libraries(){
    if(initialized) 
        return -1;
    wrap_call(int, migrate_shared_libraries_internal());
}
