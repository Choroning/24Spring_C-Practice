/**
 * @file    Example_LinkedList.c
 * @brief   A singly linked list of int values: insertion at the front and removal by value through a pointer to a pointer
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

// Returns 1 on success and 0 on failure.
int push_front(Node **head, int value)
{
    Node *n = malloc(sizeof *n);

    if (n == NULL) {
        return 0;
    }
    n->value = value;
    n->next = *head;
    *head = n;
    return 1;
}

// Removes the first node holding value. Returns 1 if a node was removed.
int remove_value(Node **head, int value)
{
    Node **link = head;

    while (*link != NULL) {
        if ((*link)->value == value) {
            Node *victim = *link;
            *link = victim->next;
            free(victim);
            return 1;
        }
        link = &(*link)->next;
    }
    return 0;
}

void print_list(const Node *head)
{
    for (const Node *p = head; p != NULL; p = p->next) {
        printf("%d -> ", p->value);
    }
    printf("NULL\n");
}

void free_list(Node **head)
{
    Node *p = *head;

    while (p != NULL) {
        Node *next = p->next;   // read next before p is freed
        free(p);
        p = next;
    }
    *head = NULL;
}

int main(void)
{
    Node *head = NULL;

    for (int v = 1; v <= 4; v++) {
        if (!push_front(&head, v * 10)) {
            printf("out of memory\n");
            free_list(&head);
            return 1;
        }
    }
    print_list(head);

    remove_value(&head, 40);    // the first node
    print_list(head);
    remove_value(&head, 20);    // a middle node
    print_list(head);
    printf("remove 99: %d\n", remove_value(&head, 99));

    free_list(&head);
    print_list(head);
    return 0;
}
