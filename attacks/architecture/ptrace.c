#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/prctl.h>
#include "libxom.h"

#define FIB_MAX 80

// Victim function
extern size_t get_fibonacci(size_t n, size_t* accumulator);

_Noreturn void victim(size_t (*get_fibonacci_xom)(size_t, size_t*)){
    size_t buf[FIB_MAX + 1];
    // Terminate when parent terminates
    prctl(PR_SET_PDEATHSIG, SIGHUP);
    for(;;)
        get_fibonacci_xom(FIB_MAX, buf);
}

int main(){
    size_t buf[FIB_MAX + 1];
    size_t (*get_fibonacci_xom)(size_t, size_t*);
    pid_t child_pid;
    struct xombuf* xbuf = xom_alloc(PAGE_SIZE);

    if(!xbuf){
        printf("Could allocate XOM buffer!\n");
    }
    xom_write(xbuf, get_fibonacci, PAGE_SIZE, 0);

    get_fibonacci_xom = xom_lock(xbuf);
    if(!get_fibonacci_xom){
        printf("Could not lock XOM buffer!\n");
        return 1;
    }

    child_pid = fork();
    if(!child_pid)
        victim(get_fibonacci_xom);

    sleep(1);

    for(unsigned i = 0; i <= FIB_MAX; i++){
        memset(buf, 0, sizeof(buf));
        printf("%u: %lu\n", i, get_fibonacci_xom(i, buf));
    }
    return 0;
}