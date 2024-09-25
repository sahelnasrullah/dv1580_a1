#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "memory_manager.h"
#include "linked_list.h"

// Initierar listan
void list_init(Node** head,size_t node_size) {
    *head = NULL;
}

// Lägger till en nod i slutet av listan
void list_insert(Node** head, int data) {
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory for new node\n");
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Lägger till en nod efter en given nod
void list_insert_after(Node* prev_node, int data) {
    if (prev_node == NULL) {
        return;
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory for new node\n");
        return;
    }

    new_node->data = data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

// Lägger till en nod före en given nod
void list_insert_before(Node** head, Node* next_node, int data) {
    if (*head == NULL || next_node == NULL) {
        return;
    }

    if (*head == next_node) {
        list_insert(head, data);
        return;
    }

    Node* current = *head;
    while (current != NULL && current->next != next_node) {
        current = current->next;
    }

    if (current != NULL) {
        Node* new_node = (Node*)mem_alloc(sizeof(Node));
        if (new_node == NULL) {
            printf("Failed to allocate memory for new node\n");
            return;
        }

        new_node->data = data;
        new_node->next = next_node;
        current->next = new_node;
    }
}

// Tar bort en nod med ett visst värde
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

// Söker efter en nod med ett visst värde
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

// Visar innehållet i listan inom ett givet intervall
void list_display_range(Node** head, Node* start_node, Node* end_node) {
    Node* current;
    if (start_node != NULL) {
        current = start_node;
    } else {
        current = *head;
    }

    printf("[");
    while (current != NULL && (end_node == NULL || current != end_node->next)) {
        printf("%d", current->data);
        current = current->next;
        if (current != NULL && (end_node == NULL || current != end_node->next)) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Visar hela listan
void list_display(Node** head) {
    list_display_range(head, *head, NULL);
}

// Räknar antalet noder i listan
int list_count_nodes(Node** head) {
    int node_counter = 0;
    Node* current = *head;
    while (current != NULL) {
        node_counter++;
        current = current->next;
    }
    return node_counter;
}

// Rensar hela listan och frigör minnet
void list_cleanup(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* next = current->next;
        mem_free(current);
        current = next;
    }
    *head = NULL;
}