#ifndef _LIBXOM_H_
#define _LIBXOM_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct xombuf;

struct xombuf* xomalloc(size_t size);
size_t xom_get_size(struct xombuf*);
int xom_write(struct xombuf* dest, const void *const src, const size_t size);
void* xom_lock(struct xombuf*);
void xom_free(struct xombuf*);

#ifdef __cplusplus
}
#endif


#endif