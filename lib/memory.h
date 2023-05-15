#ifndef MEMORY_H
#define MEMORY_H

typedef unsigned int size_t;

struct block_meta {
  size_t size;
  struct block_meta* next;
  int free;
  //int magic; // For debugging only. TODO: remove this in non-debug mode.
};

#define META_SIZE sizeof(struct block_meta)

void* malloc(size_t size);
void* nofree_malloc(size_t size);
void* calloc(size_t nelem, size_t elsize);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

#endif
