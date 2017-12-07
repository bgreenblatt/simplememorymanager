CC=gcc 
CFLAGS=-Wall -g

OBJS = bitset.o mymalloc.o main.o

all: malloc_tester
malloc_tester: bitset.o mymalloc.o main.o
	$(CC) -o $@ $(CFLAGS) $(OBJS)
bitset.o: bitset.c 
mymalloc.o: mymalloc.c 
main.o: main.c

clean:
	rm -f malloc_tester bitset.o mymalloc.o main.o
run:
	./malloc_tester
