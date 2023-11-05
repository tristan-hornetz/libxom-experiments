#include <stdio.h>
#include <errno.h>
#include "libxom.h"

typedef void (*pfun)(const char*, size_t);

const char msg[] = "Hello from asm\n";
void __attribute__((aligned(4096))) print_something(const char* pmsg, size_t len){
    asm volatile(   "mov $1, %%rdi\n"
                    "mov %1, %%rsi\n"
                    "mov %2, %%rdx\n"
                    "syscall"
                    :: "a"(1), "g"(pmsg), "g"(len)
                    : "rdi", "rsi", "rdx");
}

int main(){
    int status; 
    pfun print_protected;
    struct xombuf* buf = xomalloc(1 << 12);

    if(!buf){
        printf("Could not allocate xom buffer, errno is %d\n", errno);
        return 1;
    }

    status = xom_write(buf, print_something, 48);
    if(status < 0){
        printf("Could not write to xom buffer, errno is %d\n", errno);
        return 1;
    }
    
    print_protected = xom_lock(buf);
    if(!print_protected){
        printf("Could not lock xom buffer, errno is %d\n", errno);
        return 1;
    }

    print_protected(msg, sizeof(msg));

    xom_free(buf);
    return 0;
}