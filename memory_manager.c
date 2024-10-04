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

        // Debug
    // printf("Memory block (free_memory_array) initialized with size: %zu\n", free_memory_array->size);
    // printf("Memory left (AFTER INIT): %zu\n", memory_left);
    // printf("Memory block is free: %d\n", free_memory_array->free);
    // printf("Memory block address: %p\n", (void*)free_memory_array);
}

void* mem_alloc(size_t size) {
    // Debug: Attempting to allocate memory
    printf("\nAttempting to allocate memory of size: %zu\n", size);
    Memory_Block* current = free_memory_array;

    // Check for zero allocation
    if (size == 0) {
        printf("Requested size is 0, returning NULL.\n");
        return NULL;
    }
    
    // Check if there is enough memory left
    if (memory_left < size) {
        printf("Not enough memory left (available: %zu, requested: %zu)\n", memory_left, size);
        return NULL;
    }

    // Traverse the linked list of memory blocks
    while (current != NULL) {
        // Debug: Check each block
        printf("Checking block at %p with size %zu\n", (void*)current, current->size);

        if (current->free && current->size >= size) {
            // Found a suitable block
            printf("Found a suitable block at %p with size %zu\n", (void*)current, current->size);

            // If the block is larger than needed, split it
            if (current->size > size + sizeof(Memory_Block)) {
                Memory_Block* new_block = (Memory_Block*)((char*)current + sizeof(Memory_Block) + size);
                new_block->size = current->size - size - sizeof(Memory_Block);
                new_block->free = 1;
                new_block->next = current->next;

                // Update the current block to hold the new size
                current->size = size;
                current->next = new_block;
            }

            current->free = 0; // Mark the block as allocated
            memory_left -= size; // Decrease the available memory
            printf("Allocated block at %p, memory left: %zu\n", (void*)current, memory_left);
            return (void*)(current + 1); // Return a pointer to the data area
        }
        current = current->next;
    }

    // If no suitable block is found
    printf("Not enough memory (no suitable block found)\n");
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

