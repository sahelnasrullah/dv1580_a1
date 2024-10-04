#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "memory_manager.h"
#include "linked_list.h"

void list_init(Node** head,size_t node_size) {
    if (memory_pool == NULL) {
        size_t poolSize = node_size * 100;
        mem_init(node_size);
        printf("Memory pool initialized in list_init\n");
    }
    *head = NULL;
}

void list_insert(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory for new node (list_insert)\n");
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        // printf("Head node set to: %p (data: %d)\n", *head, (*head)->data);
    } else {
        Node* current = *head;
        // printf("Traversing to the end of the list to insert new node...\n");
        while (current->next != NULL) {
            // printf("Current node: %p (data: %d), Next node: %p\n", current, current->data, current->next);
            current = current->next;
        }
        current->next = new_node;
        // printf("Linked node %p (data: %d) to new node %p (data: %d)\n", current, current->data, new_node, new_node->data);
    }


    // printf("Head node address after insert: %p (data: %d)\n", *head, (*head)->data);
}

void list_insert_after(Node* prev_node, int data) {
    if (prev_node == NULL) {
        return;
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory for new node(list_insert_after)\n");
        return;
    }

    new_node->data = data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void list_insert_before(Node** head, Node* next_node, int data) {
    if (*head == NULL || next_node == NULL) {
        return;
    }

    if (*head == next_node) {
        Node* new_node = (Node*)mem_alloc(sizeof(Node));
        if (new_node == NULL) {
            printf("Failed to allocate memory for new node(list_insert_before)\n");
            return;
        }
        new_node->data = data;
        new_node->next = *head;  
        *head = new_node;     
        return;
    }

    Node* current = *head;
    while (current != NULL && current->next != next_node) {
        current = current->next;
    }

    if (current != NULL) {
        Node* new_node = (Node*)mem_alloc(sizeof(Node));
        if (new_node == NULL) {
            printf("Failed to allocate memory for new node(list_insert_before)\n");
            return;
        }

        new_node->data = data;
        new_node->next = next_node; 
        current->next = new_node; 
    }
}

void list_delete(Node** head, int data) {
    if (*head == NULL) {
        return;
    }

    Node* current = *head;
    Node* prev = NULL;

    if (current != NULL && current->data == data) {
        *head = current->next;
        mem_free(current);
        return;
    }

    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    prev->next = current->next;
    mem_free(current);
}

Node* list_search(Node** head, int data) {
    Node* current = *head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void list_display(Node** head) {
    printf("list_display function has been called.\n");

    Node* current = *head;
    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void list_display_range(Node** head, Node* start_node, Node* end_node) {
    if (*head == NULL || start_node == NULL) {
        printf("[]");
        return;
    }
    
    Node* current = (*head == start_node) ? *head : start_node;
    printf("[");
    
    while (current != NULL) {
        printf("%d", current->data);
        
        if (current == end_node) {
            break;
        }
        
        if (current->next != NULL && current != end_node) {
            printf(", ");
        }
        
        current = current->next;
    }
    
    printf("]");
}

int list_count_nodes(Node** head) {
    int node_counter = 0;
    Node* current = *head;
    while (current != NULL) {
        node_counter++;
        current = current->next;
    }
    return node_counter;
}

void list_cleanup(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* next = current->next;
        mem_free(current);
        current = next;
    }
    *head = NULL;
}
