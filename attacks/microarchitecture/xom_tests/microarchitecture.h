#ifndef MICROARCHITECTURE_H
#define MICROARCHITECTURE_H
#include <stdint.h>

struct attack_test;

#define OUTPUT_DIR "attack_results"

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define CRESET "\e[0m"
#define STR_OK "[" GRN "+" CRESET "] "
#define STR_PEND "[" CYN "*" CRESET "] "
#define STR_FAIL "[" RED "-" CRESET "] "

typedef union {
    struct {
        uint8_t noxom_works;
        uint8_t xom_works;
        uint8_t failed;
    } s;
    uint32_t d;
} attack_status;

static_assert(sizeof(attack_status) == sizeof((attack_status){}.d), "attack_status layout error");

typedef attack_status (*attack_test_fun)(const struct attack_test &);

struct attack_test {
    attack_test_fun test_fun;
    const char* name;
    const char* attack_class_name;
    uint8_t cross_addres_space;
    uint32_t num_samples;
    uint32_t success_fraction;

    attack_status run_test(void) const;
} typedef attack_test;


#endif //MICROARCHITECTURE_H
