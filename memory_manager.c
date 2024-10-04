#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Memory_Block {
    size_t size;  // Size of the block
    int free;     // 1 if free, 0 if used
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

    malloc(size * sizeof(Memory_Block));
    if (memory_pool == NULL) {
        printf("Failed to allocate memory pool (mem_init)\n");
        return;
    }

    free_memory_array = (Memory_Block*)memory_pool;
    free_memory_array->size = size; 
    free_memory_array->free = 1;
    free_memory_array->next = NULL;

    memory_left = size;
}

void* mem_alloc(size_t size) {
    if (size == 0 || size > memory_left) {
        return NULL; 
    }

    Memory_Block* current = free_memory_array;

    while (current != NULL) {

        if (current->free && current->size >= size) {

            if (current->size >= size) {
                Memory_Block* new_block = (Memory_Block*)((char*)current + size);
                new_block->size = current->size - size;
                new_block->free = 1;
                new_block->next = current->next;

                current->size = size;  
                current->free = 0;      
                current->next = new_block;
            } else {
                current->free = 0; 
            }

            memory_left -= current->size; 
            return (void*)(current + 1); 
        }
        current = current->next; 
    }

    return NULL;
}

void mem_free(void* block) {
    if (block == NULL) {
        return;
    }

    Memory_Block* mem_block = (Memory_Block*)block - 1; // Get the block header
    mem_block->free = 1; // Mark the block as free
    memory_left += mem_block->size + sizeof(Memory_Block); // Update memory left

    // Coalesce adjacent free blocks
    Memory_Block* current = free_memory_array;
    while (current != NULL) {
        // Check if current block is free and next block is also free
        if (current->free && current->next && current->next->free) {
            current->size += sizeof(Memory_Block) + current->next->size; // Combine sizes
            current->next = current->next->next; // Remove next block
        }
        current = current->next; // Move to the next block
    }
}

void mem_deinit() {
    free(memory_pool);
    memory_pool = NULL;
    free_memory_array = NULL;
    memory_left = 0;
}