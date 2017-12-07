#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitset.h"

struct memstruct {
        size_t max_free;
        char membuf[4096];
        struct bitset *b;
        struct memstruct *next;
        // need a field to tell allocated areas' sizes
        uint16_t allocs[4096];
};

struct memstruct *head = NULL;

struct memstruct* new_block() {
	struct memstruct *mem = NULL;
	mem = malloc(sizeof(struct memstruct));
	if (NULL == mem) {
		return NULL;
	}
	mem->b = bitset_alloc(4096);
	if (NULL == mem->b) {
		free(mem);
		return NULL;
	}
	memset(mem->membuf, 0, 4096);
	mem->max_free = 4096;
	mem->next = NULL;
	return mem;
}

struct memstruct* find_avail_memblock(size_t size) {
	struct memstruct *mem = head;

	while (mem != NULL) {
		if (mem->max_free >= size) {
			return mem;
		}
		mem = mem->next;
	}
	// never found a good memblock
	return NULL;
}

void * my_malloc(size_t size) {
	int i, j;
	struct memstruct *mem = NULL;
	if (size > 4096) {
		return NULL;
	}
	if (NULL == head) {
		head = new_block();
		if (NULL == head) {
			return NULL;
		}
	}
	mem = find_avail_memblock(size);
	if (NULL == mem) {
		mem = new_block();
		if (NULL == mem) {
			return NULL;
		}
		mem->next = head;
		head = mem;
		i = 0;
	} else {
		i = bitset_first_fit(mem->b, size);
	}
	if (-1 == i) {
		// should not happen.  we just found a good
		// memblock
		return NULL;
	}
	for (j = i; j < i + size; j++) {
		bitset_set(mem->b, j);
	}
	mem->max_free -= size;
	mem->allocs[i] = size;
	return & (mem->membuf[i]);
}

void my_free(void *loc) {
	int i, j;
	void *p1;
	struct memstruct *mem = head;

	while (mem != NULL) {
		p1 = &(mem->membuf);
		i = loc - p1;
		if ((i >= 0) && (i < 4096)) {
			break;
		}
		mem = mem->next;
	}
	if (NULL == mem) {
		// attempting to free something that we couldn't find
		// should probably assert
		return;
	}
	int16_t size = mem->allocs[i];
	for (j = i; j < i + size; j++) {
		bitset_clear(mem->b, j);
	}
	for (j = i; j < i + size; j++) {
		mem->membuf[j] = '\0';
	}
	mem->allocs[i] = 0;
}
