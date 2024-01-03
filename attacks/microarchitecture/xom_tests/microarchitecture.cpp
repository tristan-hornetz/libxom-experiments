#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "microarchitecture.h"
#include "attacks.h"

extern "C" void set_processor_affinity(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

attack_status attack_test::run_test() const {
    char logfile_path[0x100];
    snprintf(logfile_path, sizeof(logfile_path), OUTPUT_DIR "/%s.log", name);

    printf(STR_PEND "Running test '%s'...", name);
    fflush(stdout);

    if(access(OUTPUT_DIR, W_OK | X_OK))
        mkdir(OUTPUT_DIR, 0755);
    else if(!access(logfile_path, W_OK))
        remove(logfile_path);

    const auto log_fd = open(logfile_path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    const auto stdout_back = dup(1), stderr_back = dup(2);
    close(1);
    close(2);
    dup2(log_fd, 1);
    dup2(log_fd, 2);

    const auto ret = test_fun(*this);

    printf("\n");

    dup2(stdout_back, 1);
    dup2(stderr_back, 2);
    close(log_fd);

    if(ret.s.failed)
        printf("\r" STR_FAIL "Running test '%s'... Failed! See '%s' for details\n", name, logfile_path);
    else
        printf("\r" STR_OK "Running test '%s'... Done! (NOXOM: %s, XOM: %s)\n", name,
            ret.s.noxom_works ? GRN "+" CRESET : RED "-" CRESET,
            ret.s.xom_works ? GRN "+" CRESET : RED "-" CRESET);

    return ret;
}

extern "C" int ridl_generic_c(uint32_t num_samples, uint32_t success_rate);

int main(int argc, char* argv[]){
    (void) spectre_btb_ca_ip.run_test();
    (void) spectre_pht_sa_ip.run_test();
    (void) meltdown.run_test();
    //ridl_generic_c(100000, 0);
    portsmash.run_test();
    return 0;
}
