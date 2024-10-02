#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "memory_manager.h"
#include "linked_list.h"

void list_init(Node** head,size_t node_size) {
    *head = NULL;
}

void list_insert(Node** head, int data) {
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory for new node(list_insert)\n");
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

void list_display(Node** head) {
    list_display_range(head, *head, NULL);
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

// int main() {
//     // Initialize the memory pool before any list operations
//     mem_init(1024);  // Initialize 1MB memory pool

//     Node* head;
    
//     // Initialize the list
//     list_init(&head, sizeof(Node));
//     printf("List initialized. \n");

//     // Edge Case 1: Delete from an empty list
//     printf("Attempting to delete node from empty list...\n");
//     list_delete(&head, 10);
//     list_display(&head);  // Should display []

//     // Edge Case 2: Search in an empty list
//     printf("Searching for node in empty list...\n");
//     Node* found = list_search(&head, 10);
//     if (found) {
//         printf("Node with data 10 found.\n");
//     } else {
//         printf("Node with data 10 not found.\n");  // Expected
//     }

//     // Inserting nodes into the list
//     printf("Inserting nodes into the list...\n");
//     list_insert(&head, 5);
//     list_insert(&head, 10);
//     list_insert(&head, 15);
//     list_display(&head);  // Should display [5, 10, 15]

//     // Edge Case 3: Delete a non-existent node (20)
//     printf("Attempting to delete a non-existent node (20)...\n");
//     list_delete(&head, 20);  // Should not crash or affect list
//     list_display(&head);  // Should still display [5, 10, 15]

//     // Search for an existing node
//     printf("Searching for node with data 10...\n");
//     found = list_search(&head, 10);
//     if (found) {
//         printf("Node with data 10 found.\n");  // Expected
//     } else {
//         printf("Node with data 10 not found.\n");
//     }

//     // Search for a non-existent node
//     printf("Searching for node with data 20...\n");
//     found = list_search(&head, 20);
//     if (found) {
//         printf("Node with data 20 found.\n");
//     } else {
//         printf("Node with data 20 not found.\n");  // Expected
//     }

//     // Edge Case 4: Delete the head node
//     printf("Deleting the head node (5)...\n");
//     list_delete(&head, 5);
//     list_display(&head);  // Should display [10, 15]

//     // Edge Case 5: Delete the last node
//     printf("Deleting the last node (15)...\n");
//     list_delete(&head, 15);
//     list_display(&head);  // Should display [10]

//     // Edge Case 6: Delete the only remaining node
//     printf("Deleting the only remaining node (10)...\n");
//     list_delete(&head, 10);
//     list_display(&head);  // Should display []

//     // Edge Case 7: Cleanup an already empty list
//     printf("Cleaning up the empty list...\n");
//     list_cleanup(&head);  // Should not crash
//     list_display(&head);  // Should display []

//     // Inserting nodes again to test list_cleanup
//     printf("Inserting nodes (5, 10, 15) again for cleanup test...\n");
//     list_insert(&head, 5);
//     list_insert(&head, 10);
//     list_insert(&head, 15);
//     list_display(&head);  // Should display [5, 10, 15]

//     // Edge Case 8: Cleanup with multiple nodes
//     printf("Cleaning up the list with multiple nodes...\n");
//     list_cleanup(&head);  // Should free all nodes
//     list_display(&head);  // Should display []

//     return 0;
// }