# simplememorymanager
This provides a simple memory manager that can be used for small mallocs (i.e. &lt; 4KB)

The metadata overhead for each 4KB block is 8KB for the allocs field that specifies the size of each allocated chunk.
There is also a bitset field in the metadata with one bit for each byte in the block, that specifies whether the block is in use or not.  This adds another 512 bytes overhead.

A call to mymalloc iterates through the block list until it finds a block with enough free space.  Once a good block is found, the bits in the bitset are set to 1 for the allocated byte range.  If there are no blocks in the block list with enough free space, then a new block is allocated and inserted at the front of the list.

A call to myfree iterates through the block list until it finds the block from which the specified location was allocated.  Once the block is found, the bits in the bitset are reset back to 0 to indicate the area is now free for use.  Once the memory is freed, the bytes in the free area are also reset back to zero.
