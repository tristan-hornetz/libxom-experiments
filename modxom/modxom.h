#ifndef _MODXOM_H_
#define _MODXOM_H_

#ifndef __KERNEL__
#include <stdint.h>
#endif

#define MODXOM_CMD_NOP      0
#define MODXOM_CMD_FREE     1
#define MODXOM_CMD_LOCK     2

struct {
    uint32_t cmd;
    uint32_t num_pages;
    uintptr_t base_addr;
} typedef modxom_cmd, *pmodxom_cmd;

#endif