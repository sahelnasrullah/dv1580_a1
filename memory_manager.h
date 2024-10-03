#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdlib.h>

typedef struct Memory_Block {
    size_t size;
    int free;  
    struct Memory_Block* next;
} Memory_Block;


extern void* memory_pool;
extern Memory_Block* free_memory_array;
extern size_t memory_left;

void mem_init(size_t size);
void* mem_alloc(size_t size);
void mem_free(void* block);
void* mem_resize(void* block, size_t new_size);
void mem_deinit();

#endif 