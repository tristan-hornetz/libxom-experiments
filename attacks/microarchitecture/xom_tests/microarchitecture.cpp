#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "microarchitecture.h"

int main_btb(int argc, char* argv[]);

attack_status attack_test::run_test() const {
    char logfile_path[0x100];
    snprintf(logfile_path, sizeof(logfile_path), OUTPUT_DIR "/%s.log", name);

    printf(STR_PEND "Running test '%s'...", name);
    fflush(stdout);

    const auto log_fd = open(logfile_path, O_WRONLY | O_CREAT);
    const auto stdout_back = dup(1), stderr_back = dup(2);
    close(1);
    close(2);
    dup2(log_fd, 1);
    dup2(log_fd, 2);

    const auto ret = test_fun(*this);

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

extern attack_test spectre_btb_ca;

int main(int argc, char* argv[]){
    (void) spectre_btb_ca.run_test();
    return 0;
}
