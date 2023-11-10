#ifndef _LIBXOM_H_
#define _LIBXOM_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/** An anonymous struct describing a XOM buffer.
 * To obtain the executable buffer itself, use xom_lock.
*/
struct xombuf;


/** Allocate a XOM buffer.
 * This buffer will have RWX permissions until xom_lock is called, so make sure
 * that you do not leave the XOM buffer unlocked for longer that necessary.
 *  
 * @param size The size of the XOM buffer
 * @returns NULL upon failure, a pointer != NULL otherwise.
 *  This is not the address of the executable memory region itself, which can be 
 *  obtained with xom_lock.
 */
struct xombuf* xom_alloc(size_t size);


/** Get the size of a XOM buffer
 * @param buf The XOM buffer
 * @returns The XOM buffer's size
*/
size_t xom_get_size(struct xombuf* buf);


/** Write into a XOM buffer.
 * 
 * @param dest The XOM buffer to write into
 * @param src The source buffer
 * @param size The number of bytes to copy. The caller must make sure that the 
 *  length of src is >= size
 * @returns If successful, it returns the number of bytes copied. Otherwise, a
 *  value < 0 is returned and errno is set
*/
int xom_write(struct xombuf* dest, const void *const src, const size_t size);

/** Lock a XOM buffer.
 * 
 * @param buf The XOM buffer to lock.
 * @return The address of the newly allocated XOM memory region, or NULL if the function fails 
*/
void* xom_lock(struct xombuf* buf);

/** Free a XOM buffer.
 * 
 * @param buf The XOM buffer to be freed.
*/
void xom_free(struct xombuf*);

/** Migrate all executable memory regions that are currently in the address space to XOM.
 * This function can only be called once, and only if no other function from libxom has been
 * called before. Typically, it should be called at the beginning of main.
 * 
 * @returns 0 upon success, a negative value otherwise
*/
int xom_migrate_all_code();


/** Migrate the code of all shared libraries that is currently in the address space to XOM.
 * This function can only be called once, and only if no other function from libxom has been
 * called before. Typically, it should be called at the beginning of main.
 * 
 * @returns 0 upon success, a negative value otherwise
*/
int xom_migrate_shared_libraries();

#ifdef __cplusplus
}
#endif


#endif