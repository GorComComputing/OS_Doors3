#include "memory.h"
#include "string.h"


void* global_base = 0;


struct block_meta* find_free_block(struct block_meta** last, size_t size) {
  struct block_meta* current = global_base;
  while(current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}


struct block_meta* request_space(struct block_meta* last, size_t size) {
  struct block_meta* block;
  block = brk(0);
  void* request = brk(block + size + META_SIZE);
  //assert((void*)block == request); // Not thread safe.
  if (request == (void*) -1) {
  	static const char msg_failed[] = "sbrk failed\n";
  	write(1, msg_failed, strlen(msg_failed));
    	return 0; // sbrk failed.
  }

  if (last) { // NULL on first request.
    last->next = block;
  }
  block->size = size;
  block->next = 0;
  block->free = 0;
  //block->magic = 0x12345678;
  return block;
}


void* malloc(size_t size) {
  struct block_meta* block;
  // TODO: align size?

  if (size <= 0) {
    return 0;
  }

  if(!global_base){ // First call.
    block = request_space(0, size);
    if (!block) {
      return 0;
    }
    global_base = block;
  } else {
    struct block_meta* last = global_base;
    block = find_free_block(&last, size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);
      if (!block) {
        return 0;
      }
    } else {      // Found free block
      // TODO: consider splitting block here.
      block->free = 0;
      //block->magic = 0x77777777;
    }
  }

  return(block + 1);
}


void* nofree_malloc(size_t size){
	void* p = brk(0);
  	void* request = brk(p + size);
  	if(request == (void*) -1) {
  		static const char msg_failed[] = "sbrk failed\n";
  		write(1, msg_failed, strlen(msg_failed));
    		return 0; // sbrk failed.
  	} else{
    		//if(p == request){
    			static const char msg_succ[] = "sbrk succ\n";
  			write(1, msg_succ, strlen(msg_succ));
  		//}
    		return p;
  	}
}


void* calloc(size_t nelem, size_t elsize){
  size_t size = nelem * elsize;
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}


struct block_meta* get_block_ptr(void* ptr) {
  return (struct block_meta*)ptr - 1;
}


void free(void* ptr) {
  if (!ptr) {
    return;
  }

  // TODO: consider merging blocks once splitting blocks is implemented.
  struct block_meta* block_ptr = get_block_ptr(ptr);
  //assert(block_ptr->free == 0);
  //assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
  block_ptr->free = 1;
  //block_ptr->magic = 0x55555555;
}


void* realloc(void* ptr, size_t size){
  if (!ptr) { 
    // NULL ptr. realloc should act like malloc.
    return malloc(size);
  }

  struct block_meta* block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size) {
    // We have enough space. Could free some once we implement split.
    return ptr;
  }

  // Need to really realloc. Malloc new space and free old space.
  // Then copy old data to new space.
  void* new_ptr;
  new_ptr = malloc(size);
  if (!new_ptr) {
    return 0; // TODO: set errno on failure.
  }
  memcpy(new_ptr, ptr, block_ptr->size);
  free(ptr);  
  return new_ptr;
}



