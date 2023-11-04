#include <stdint.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libxom.h"
#include "modxom.h"

#define PAGE_SIZE   0x1000
#define PAGE_SHIFT  12
#define SIZE_CEIL(S) (((S) & ~(PAGE_SIZE - 1)) + (((S) & ~(PAGE_SIZE - 1)) ? PAGE_SIZE : 0))

struct xombuf {
    void* address;
    size_t allocated_size;
    uint8_t locked;
} __attribute__((packed)) typedef _xombuf, *p_xombuf;

static volatile uint8_t initialized = 0;
static pthread_mutex_t lib_lock;
int xomfd = -1;

#define wrap_call(T, F) {           \
    T r;                            \
    __libxom_prologue();            \
    r = F;                          \
    __libxom_epilogue();            \
    return r;                       \
}

static void __libxom_prologue(){
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
    return;
}

static inline void __libxom_epilogue(){
    pthread_mutex_unlock(&lib_lock);
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
    if(!ret->address)
        return NULL;
    
    ret->allocated_size = size;
    ret->locked = 0;
    return ret;
}

static inline int xom_write_internal(struct xombuf* dest, const unsigned char* src, const size_t size){
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

struct xombuf* xomalloc(size_t size){
    wrap_call(struct xombuf*, xomalloc_internal(size));
}

size_t xom_get_size(struct xombuf* buf){
    return buf->allocated_size;
}

int xom_write(struct xombuf* dest, const unsigned char* src, const size_t size){
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

