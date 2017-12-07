#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitset.h"
#include "mymalloc.h"

int main() {
	char *mem1 = NULL, *mem2 = NULL, *mem3 = NULL, *mem4 = NULL;

	mem1 = my_malloc(128);
	strcpy(mem1, "hello");
	printf("mem1: %s\n", mem1);
	mem2 = my_malloc(12);
	strcpy(mem2, "hello");
	printf("mem2: %s\n", mem2);
	mem3 = my_malloc(28);
	strcpy(mem3, "hello");
	printf("mem3: %s\n", mem3);
	mem4 = my_malloc(4000);
	strcpy(mem4, "longer memory alloc");
	printf("mem4: %s\n", mem4);
	my_free(mem1);
	mem1 = my_malloc(256);
	strcpy(mem1, "hello again");
	printf("mem1: %s\n", mem1);
	my_free(mem2);
	my_free(mem3);
	my_free(mem4);
	my_free(mem1);
}
