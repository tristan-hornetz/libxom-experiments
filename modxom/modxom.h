#ifndef _MODXOM_H_
#define _MODXOM_H_

#ifndef __KERNEL__
#include <stdint.h>
#endif

#define MODXOM_CMD_NOP              0
#define MODXOM_CMD_FREE             1
#define MODXOM_CMD_LOCK             2
#define MODXOM_CMD_INIT_SUBPAGES    3
#define MODXOM_CMD_WRITE_SUBPAGES   4

#ifdef __cplusplus
extern "C" {
#endif

struct {
    uint32_t cmd;
    uint32_t num_pages;
    uintptr_t base_addr;
} typedef modxom_cmd, *pmodxom_cmd;


#ifdef __cplusplus
}
#endif

#endif