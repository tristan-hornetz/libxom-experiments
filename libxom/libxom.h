/** \file libxom.h
 * A brief file description.
 * A more elaborated file description.
 */

#ifndef _LIBXOM_H_
#define _LIBXOM_H_

#include <stdlib.h>
#include <stdint.h>

#ifndef PAGE_SIZE
#define PAGE_SIZE 0x1000
#define PAGE_SHIFT 12
#endif

#ifndef SUBPAGE_SIZE
#define SUBPAGE_SIZE (PAGE_SIZE / (sizeof(uint32_t) << 3))
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * An anonymous struct describing a XOM buffer.
 * To obtain the executable buffer itself, use xom_lock.
*/
struct xombuf;
struct xom_subpages;


/** 
 * Allocate a XOM buffer.
 * This buffer will have RWX permissions until xom_lock is called, so make sure
 * that you do not leave the XOM buffer unlocked for longer that necessary.
 * XOM buffers are created on the order of pages, which means that the smallest
 * possible XOM buffer takes up at least 4KB of memory, even if a size smaller
 * than that is specified. If need to repeatedly allocate small chunks of XOM,
 * xom_alloc_subpages instead.
 *  
 * @param size The size of the XOM buffer
 * @returns NULL upon failure, a pointer != NULL otherwise.
 *  This is not the address of the executable memory region itself, which can be 
 *  obtained with xom_lock.
 */
struct xombuf* xom_alloc_pages(size_t size);

/**
 * @returns 1 if XOM is supported in the current environment, 0 otherwise
 */
int is_xom_supported();

/** 
 * Get the size of a XOM buffer
 * @param buf The XOM buffer
 * @returns The XOM buffer's size
*/
size_t xom_get_size(struct xombuf* buf);


/** 
 * Write into a XOM buffer.
 * 
 * @param dest The XOM buffer to write into
 * @param src The source buffer
 * @param size The number of bytes to copy. The caller must make sure that the 
 *  length of src is >= size
 * @returns If successful, it returns the number of bytes copied. Otherwise, a
 *  value < 0 is returned and errno is set
*/
int xom_write(struct xombuf* dest, const void *const src, const size_t size);

/** 
 * Lock a XOM buffer.
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

/** 
 * Migrate all executable memory regions that are currently in the address space to XOM.
 * This function can only be called once, and only if no other function from libxom has been
 * called before. Typically, it should be called at the beginning of main.
 * 
 * @returns 0 upon success, a negative value otherwise
*/
int xom_migrate_all_code();

/** 
 * Migrate the code of all shared libraries that are currently in the address space to XOM.
 * This function can only be called once, and only if no other function from libxom has been
 * called before. Typically, it should be called at the beginning of main.
 * 
 * @returns 0 upon success, a negative value otherwise
*/
int xom_migrate_shared_libraries();

/**
 * Allocate a section of XOM that is organized as 128-byte subpages, which can be filled 
 * independently of each other.
 * 
 * @param size The size of the subpage XOM buffer
 * @returns If this function fails, it returns NULL and sets errno. Otherwise, a pointer
 *  > NULL is returned
*/
struct xom_subpages* xom_alloc_subpages(size_t size);

/**
 * Search for a contiguous sequence of subpages that is large enough to contain the data
 * in src. If found, the data in src is written into these subpages, which are then locked.
 * Note that each write will occupy at least one 128-byte subpage, so even a 1-byte write
 * will reserve 128-bytes in memory. 
 * 
 * @param dest A subpage XOM buffer previously allocated with xom_alloc_subpages
 * @param size The size of the data in src in bytes
 * @param src A buffer containing the data to be written into XOM
 * @returns If this function fails, it returns NULL and sets errno. ENOMEM indicates that
 * no contiguous sequence of subpages was found that is large enough to store the data in 
 * src. If successful, the function returns a pointer to the start of the memory chunk that
 * was written to.
*/
void* xom_fill_and_lock_subpages(struct xom_subpages* dest, size_t size, const void *const src);

/**
 * Free a XOM buffer that was obtained through xom_fill_and_lock_subpages. Note
 * that this may not release the subpages immediately, as they remain locked in 
 * memory. The subpages are only marked as unused until all subpages in the XOM
 * buffer have been freed with this function. Only then is the memory actually
 * released.
 * 
 * @param subpages A subpage XOM buffer previously allocated with xom_alloc_subpages
 * @param base_address A pointer previously obtained through xom_fill_and_lock_subpages
 * 
 * @returns -1 if the function fails, 0 if there are still subpages in the buffer that
 *  are in use, and 1 if the subpage XOM buffer was fully freed and removed from memory.
*/
int xom_free_subpages(struct xom_subpages* subpages, void* base_address);

/**
 * Free all subpages in the subpage XOM buffer.
 * 
 * @param subpages A subpage XOM buffer previously allocated with xom_alloc_subpages
*/
void xom_free_all_subpages(struct xom_subpages* subpages);

#ifdef __cplusplus
}
#endif


#endif