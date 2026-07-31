#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    void *data;
    char type[10];
    struct Node *next;
};

struct LinkedList {
    struct Node *head;
    int size;
};

struct LinkedList *createList() {
    struct LinkedList *list = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    if (list == NULL) {
        printf("Error: memory allocation failed for List\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void add_at_end(struct LinkedList *list, void *data, const char *type) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: memory allocation failed for List\n");
        return;
    }

    newNode->data = data;
    strcpy(newNode->type, type);
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void add_at_middle(struct LinkedList *list, void *data, const char *type, int index) {
    if (index < 0 || index > list->size) {
        printf("Error: Invalid index.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: memory allocation failed for List\n");
        return;
    }

    newNode->data = data;
    strcpy(newNode->type, type);

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct Node *prev = list->head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        newNode->next = prev->next;
        prev->next = newNode;
    }

    list->size++;
}

void remove_at_index(struct LinkedList *list, int index) {
    if (list->head == NULL) {
        printf("Error: List is empty.\n");
        return;
    }
    if (index < 0 || index >= list->size) {
        printf("Error: Invalid index.\n");
        return;
    }

    struct Node *temp = list->head;

    if (index == 0) {
        list->head = temp->next;
        free(temp->data);
        free(temp);
        list->size--;
        return;
    }

    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    struct Node *node_to_remove = temp->next;
    temp->next = node_to_remove->next;

    free(node_to_remove->data);
    free(node_to_remove);
    list->size--;
}

int getSize(struct LinkedList *list) {
    return list->size;
}

void display_list(struct LinkedList *list) {
    struct Node *current = list->head;

    while (current != NULL) {
        if (strcmp(current->type, "int") == 0) {
            printf("[INT: %d] -> ", *(int *)current->data);
        }
        else if (strcmp(current->type, "float") == 0) {
            printf("[FLOAT: %.2f] -> ", *(float *)current->data);
        }
        else if (strcmp(current->type, "string") == 0) {
            printf("[STRING: %s] -> ", (char *)current->data);
        }
        else {
            printf("[UNKNOWN TYPE] -> ");
        }

        current = current->next;
    }

    printf("NULL\n");
}

void free_list(struct LinkedList *list) {
    struct Node *current = list->head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int main() {
    struct LinkedList *myList = createList();

    int *int_data = (int *)malloc(sizeof(int));
    *int_data = 100;

    float *float_data = (float *)malloc(sizeof(float));
    *float_data = 200.5f;

    char *str_data = strdup("Hello");

    add_at_end(myList, int_data, "int");
    add_at_end(myList, float_data, "float");

    printf("After adding 2 elements at the end\n");
    display_list(myList);

    printf("\nInsert 'Hello' (string) at index 1\n");
    add_at_middle(myList, str_data, "string", 1);
    display_list(myList);

    printf("\nCurrent size of list\n");
    printf("Size: %d\n", getSize(myList));

    printf("\nRemoving element at index 1\n");
    remove_at_index(myList, 1);
    display_list(myList);
    printf("Size after removal: %d\n", getSize(myList));

    free_list(myList);
    return 0;
}
