#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "libxom.h"

// This is the function we want to move into XOM
// We link it into the .data section, so that we can overwrite it later
// Note that in a real-world application, such functions are typically
// created at runtime
unsigned int __attribute__((section(".data")))
    secret_encryption_function (unsigned int plain_text) {
    // Just XOR to keep it simple
    return plain_text ^ 0xcafebabe;
}
void __attribute__((section(".data"))) secret_encryption_function_end (void) {}


int main(int argc, char* argv[]) {
    // Get the secret function's size
    const size_t secret_function_size =
                (size_t) secret_encryption_function_end -
                (size_t) secret_encryption_function;

    unsigned int (*secret_function_xom)(unsigned int);
    int status;

    // 'struct xombuf' is an anonymous struct representing one or more XOM pages
    struct xombuf* xbuf;

    unsigned int plain_text = 0xdeadbeef;
    unsigned int cipher_text;

    // Abort if XOM is not supported
    if(get_xom_mode() == XOM_MODE_UNSUPPORTED)
        return 1;

    // Allocate a XOM buffer consisting of a single page
    xbuf = xom_alloc(PAGE_SIZE);
    if(!xbuf)
        return errno;

    // Write the secret function into the XOM buffer at offset 0
    status = xom_write(xbuf, secret_encryption_function, secret_function_size, 0);
    if(status <= 0)
        return errno;

    // Lock the XOM buffer, function returns a pointer to the XOM page itself
    secret_function_xom = xom_lock(xbuf);
    if(!secret_function_xom)
        return errno;

    // Overwrite the original function, key is now purged from readable memory
    memset(secret_encryption_function, 0, secret_function_size);

    if(get_xom_mode() == XOM_MODE_SLAT) {
        // Mark the page for full register clearing if supported
        // The second parameter can alternatively be 0 for vector-register clearing
        status = xom_mark_register_clear(xbuf, 1, 0);
        if (status < 0)
            return -status;
    }

    // Call the function in XOM
    // The following block restarts when full register clearing occurs
    expect_full_register_clear {
        cipher_text = secret_function_xom(plain_text);
    }

    printf("Cipher Text: 0x%x\n", cipher_text);

    // Free the XOM buffer
    xom_free(xbuf);

    return 0;
}

