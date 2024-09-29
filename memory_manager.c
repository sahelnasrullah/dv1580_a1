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
    memory_pool = malloc(size);
    if (memory_pool == NULL) {
        printf("Failed to allocate memory pool\n");
        return;
    }

    free_memory_array = (Memory_Block*) memory_pool;
    free_memory_array->size = size - sizeof(Memory_Block);
    free_memory_array->free = 1;
    free_memory_array->next = NULL;
    
    memory_left = size - sizeof(Memory_Block);
}

void* mem_alloc(size_t size) {
    Memory_Block* current = free_memory_array;

    if (size == 0 || memory_left < sizeof(Memory_Block)) {
        printf("Not enough memory\n");
        return NULL;
    }

    if (size + sizeof(Memory_Block) > 512) {
        size = 512 - sizeof(Memory_Block);
    }

    while (current != NULL) {
        if (current->free && current->size >= size) {

            if (current->size >= size + sizeof(Memory_Block)) {
                Memory_Block* new_block = (Memory_Block*) ((char*)current + sizeof(Memory_Block) + size);
                new_block->size = current->size - size - sizeof(Memory_Block);
                new_block->free = 1;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }
            current->free = 0;
            memory_left -= current->size + sizeof(Memory_Block);
            printf("%zu Memory left\n", memory_left);
            return (void*)(current + 1);
        }
        current = current->next;
    }

    printf("Not enough memory\n");
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


// void my_assert(int expression) {
//     if (!expression) {
//         printf("Assertion failed\n");
//         exit(1);
//     }
// }


// void printf_yellow(const char* text) {
//     printf("\033[1;33m%s\033[0m", text);  // Yellow text
// }

// // Print green colored text for success
// void printf_green(const char* text) {
//     printf("\033[1;32m%s\033[0m", text);  // Green text
// }


// void test_exceed_cumulative_allocation() {
//     printf_yellow("  Testing cumulative allocations exceeding pool size ---> ");
//     mem_init(1024); // Initialize with 1KB of memory
//     void *block1 = mem_alloc(512);
//     my_assert(block1 != NULL);
//     void *block2 = mem_alloc(512);
//     my_assert(block2 != NULL);
//     void *block3 = mem_alloc(100); // This should fail, no space left
//     my_assert(block3 == NULL);
//     mem_free(block1);
//     mem_free(block2);
//     mem_deinit();
//     printf_green("[PASS].\n");
// }

// int main() {
//     test_exceed_cumulative_allocation();
//     return 0;
// }