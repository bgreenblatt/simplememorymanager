#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bitset {
	unsigned int size;
	unsigned char *bits;
};

struct bitset * bitset_alloc(unsigned int numbits) {
	struct bitset *temp = NULL;
	unsigned int size_to_alloc = 0;

	if (0 == numbits) {
		return NULL;
	}
	temp = malloc(sizeof(struct bitset));
	if (NULL == temp) {
		return NULL;
	}
	temp->size = numbits;

	size_to_alloc = 1 + (numbits / (8 * sizeof(unsigned char)));
	temp->bits = malloc(size_to_alloc);
	if (NULL == temp->bits) {
		free(temp);
		return NULL;
	}
	memset(temp->bits, 0, size_to_alloc);
	return temp;
}

void bitset_free(struct bitset **b) {
	if ((NULL == b) || (NULL == *b)) {
		return;
	}
	if (NULL != (*b)->bits) {
		free((*b)->bits);
	}
	free(*b);
	*b = NULL;
}

unsigned int bitset_get(struct bitset *b, unsigned int i) {
	unsigned char temp;
	unsigned int pos, bit_pos;
	if (NULL == b) {
		return -1;
	}
	if (i >= b->size) {
		return -1;
	}
	pos = (i / (8 * sizeof(unsigned char)));
	temp = b->bits[pos];
	bit_pos = i % 8;
	return (temp >> bit_pos) & 0x01;
}

void bitset_clear(struct bitset *b, unsigned int i) {
	unsigned char *temp;
	unsigned char bit;
	unsigned int pos, bit_pos;
	if (NULL == b) {
		return;
	}
	if (i >= b->size) {
		return;
	}
	pos = (i / (8 * sizeof(unsigned char)));
	temp = &(b->bits[pos]);
	bit_pos = i % 8;
	bit = 1 << bit_pos;
	*temp = (*temp) & ~bit;
}

void bitset_set(struct bitset *b, unsigned int i) {
	unsigned char *temp;
	unsigned char bit;
	unsigned int pos, bit_pos;
	if (NULL == b) {
		return;
	}
	if (i >= b->size) {
		return;
	}
	pos = (i / (8 * sizeof(unsigned char)));
	temp = &(b->bits[pos]);
	bit_pos = i % 8;
	bit = 1 << bit_pos;
	*temp = (*temp) | bit;
}

void bitset_print(struct bitset *b) {
	unsigned int i;

	if (NULL == b) {
		printf("bitset: NULL\n");
		return;
	}
	printf("bitset size: %d\n", b->size);
	for (i = 0; i < b->size; i++) {
		if (bitset_get(b, i) == 0) {
			printf("0");
		} else {
			printf("1");
		}
		if (((i + 1) % 8) == 0) {
			printf(" ");
		}
	}
	printf("\n");
}

unsigned int bitset_max_contiguous(struct bitset *b, unsigned int val) {
	unsigned int ret = 0, i = 0, prev = 0, next = 0, current_run = 0;
	if (NULL == b) {
		return 0;
	}
	prev = bitset_get(b, 0);
	if (prev == val) {
		current_run = 1;
	}
	for (i = 1; i < b->size; i++) {
		next = bitset_get(b, i);
		if ((next == val) && (prev == val)) {
			current_run += 1;
		} else if (next == val) {
			current_run = 1;
		} else {
			if (current_run > ret) {
				ret = current_run;
			}
			current_run = 0;
		}
		prev = next;
	}
	if (current_run > ret) {
		ret = current_run;
	}
	return ret;
}

int bitset_first_fit(struct bitset *b, unsigned int size) {
	unsigned int i = 0, prev = 0, next = 0, current_run = 0;
	prev = bitset_get(b, 0);
	if (prev == 0) {
		current_run = 1;
	}
	for (i = 1; i < b->size; i++) {
		if (current_run == size) {
			return i - size;
		}
		next = bitset_get(b, i);
		if ((next == 0) && (prev == 0)) {
			current_run += 1;
		} else if (next == 0) {
			current_run = 1;
		} else {
			current_run = 0;
		}
		prev = next;
	}
	return -1;
}
