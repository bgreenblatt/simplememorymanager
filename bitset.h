
struct bitset {
	unsigned int size;
	unsigned char *bits;
};

struct bitset * bitset_alloc(unsigned int numbits);
void bitset_free(struct bitset **b);
unsigned int bitset_get(struct bitset *b, unsigned int i);
void bitset_clear(struct bitset *b, unsigned int i);
void bitset_set(struct bitset *b, unsigned int i);
void bitset_print(struct bitset *b);
unsigned int bitset_max_contiguous(struct bitset *b, unsigned int val);
unsigned int bitset_first_fit(struct bitset *b, unsigned int size);
