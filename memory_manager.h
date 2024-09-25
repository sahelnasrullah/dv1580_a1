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

void mem_init(size_t size);
void* mem_alloc(size_t size);
void mem_free(void* block);
void mem_deinit();

#endif 