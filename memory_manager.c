#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Memory_Block {
    size_t size;
    int free;  // 1 if free, 0 if used
    struct Memory_Block* next;
} Memory_Block;

void* memory_pool = NULL;
Memory_Block* free_memory_array = NULL;
size_t memory_left = 0;

void mem_init(size_t size) {
    if (size == 0) {
        printf("Error: Cannot initialize memory pool with size 0\n");
        return;
    }

    //printf("Initializing memory pool with size: %zu\n", size);
    
    memory_pool = malloc(size);
    if (memory_pool == NULL) {
        printf("Failed to allocate memory pool (mem_init)\n");
        return;
    }

    free_memory_array = (Memory_Block*) memory_pool;

    free_memory_array->size = size; 
    free_memory_array->free = 1;
    free_memory_array->next = NULL;
    
    memory_left = free_memory_array->size;


}

void* mem_alloc(size_t size) {

    Memory_Block* current = free_memory_array;



    if (size == 0) {
        return NULL;
    }
    if (memory_left < size) {
        printf("Not eNoUgH memory (size is 0 or memory left is < than size)\n");
        return NULL;
    }

    while (current != NULL) {
        if (current->free && current->size >= size) {
            //printf("Found a free block with size: %zu\n", current->size);

            if (current->size >= size) { 
                Memory_Block* new_block = (Memory_Block*) ((char*)current + sizeof(Memory_Block) + size);
                new_block->size = current->size - size;
                new_block->free = 1;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }

            current->free = 0;
            memory_left -= size; 
            //printf("%zu Memory left\n", memory_left);
            return (void*)(current + 1);  
        }
        current = current->next;
    }

    printf("Not enough memory (there isn't really any memory)\n");
    return NULL;
}

void mem_free(void* block) {
    if (block == NULL) {
        return;
    }

    Memory_Block* mem_block = (Memory_Block*)block - 1;
    mem_block->free = 1;
    memory_left += mem_block->size + sizeof(Memory_Block);

    Memory_Block* current = free_memory_array;
    while (current != NULL) {
        if (current->free && current->next && current->next->free) {
            current->size += sizeof(Memory_Block) + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void* mem_resize(void* block, size_t new_size) {
    if (block == NULL) {
        return mem_alloc(new_size);
    }

    Memory_Block* mem_block = (Memory_Block*)block - 1;

    if (mem_block->size >= new_size) {
        return block;
    }

    void* new_block = mem_alloc(new_size);
    if (new_block != NULL) {
        memcpy(new_block, block, mem_block->size);
        mem_free(block);
    }

    return new_block;
}

void mem_deinit() {
    free(memory_pool);
    memory_pool = NULL;
    free_memory_array = NULL;
    memory_left = 0;
}