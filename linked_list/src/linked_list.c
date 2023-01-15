#include "linked_list.h"
#include <stdio.h>


struct Node *create_node(char *value)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->value = malloc(strlen(value) + 1);
    new_node->value = value;
    new_node->next_node = NULL;
    new_node->prev_node = NULL;
    return new_node;
}

struct LinkedList *create_list()
{
    struct LinkedList *ll = malloc(sizeof(struct LinkedList));
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

struct LinkedList *create_list_with_head(char *value)
{
    struct LinkedList *ll = malloc(sizeof(struct LinkedList));
    ll->head = create_node(value);
    ll->tail = NULL;
    return ll;
}

void add_new_head(struct LinkedList *ll, char *value)
{
    struct Node *new_node = create_node(value);
    if(ll->head == NULL) {
        ll->tail = new_node;
    } else {
        ll->head->prev_node = new_node;
    }
    new_node->next_node = ll->head;
    ll->head = new_node;
}

void add_new_tail(struct LinkedList *ll, char *value)
{
    struct Node *new_node = create_node(value);
    if(ll->tail == NULL) {
        ll->tail = new_node;
    } else {
        ll->tail->next_node = new_node;
        new_node->prev_node = ll->tail;
    }
    ll->tail = new_node;
}

void add_at_index(struct LinkedList *ll, size_t idx, char *value)
{
    struct Node *new_node = create_node(value);
    struct Node *cur_node = ll->head;

    for(size_t i = 0; i < idx || cur_node->next_node != NULL; i++) {
        cur_node = cur_node->next_node;
    }

    cur_node->prev_node->next_node = new_node;
    new_node->prev_node = cur_node->prev_node;
    new_node->next_node = cur_node;
    cur_node->prev_node = new_node;
}

bool is_empty(struct LinkedList ll)
{
    return ll.head == NULL;
}

char *get_head(struct LinkedList ll)
{
    if(ll.head == NULL)
        puts("List is empty.");
    else
        return ll.head->value;
    return NULL;
}

char *get_index(struct LinkedList ll, size_t idx)
{
    struct Node *cur = ll.head;
    for(size_t i = 0; i < idx; i++) {
        if(cur->next_node != NULL) {
            cur = cur->next_node;
        } else {
            printf("Reached end of list. Returning item value in list.");
            break;
        }
    }

    return cur->value;
}

char *get_tail(struct LinkedList ll)
{
    if(ll.head == NULL)
        puts("List is empty, or there is only one item in the list.");
    else
        return ll.tail->value;
    return NULL;
}

void remove_head(struct LinkedList *ll)
{
    if(ll->head == NULL) {
        puts("List is empty.");
    } else {
        struct Node *old_head = ll->head;
        struct Node *new_head = ll->head->next_node;
        ll->head = new_head;
        new_head->prev_node = NULL;
        old_head->next_node = NULL;
        free(old_head);
    }
}

void remove_tail(struct LinkedList *ll)
{
    if(ll->tail == NULL) {
        puts("List is empty, or there is only one item in the list.");
    } else {
        struct Node *old_tail = ll->tail;
        struct Node *new_tail = ll->tail->prev_node;
        ll->tail = new_tail;
        new_tail->next_node = NULL;
        old_tail->prev_node = NULL;
        free(old_tail);
    }
}

void remove_node(struct LinkedList *ll, struct Node *node)
{
    if(node == ll->head) {
        remove_head(ll);
        return;
    } else if(node == ll->tail) {
        remove_tail(ll);
        return;
    }

    struct Node *prev_node = node->prev_node;
    struct Node *next_node = node->next_node;
    prev_node->next_node = next_node;
    next_node->prev_node = prev_node;
    node = NULL;
    free(node);
}

void remove_at_index(struct LinkedList *ll, size_t idx)
{
    struct Node *cur_node = ll->head;
    for(size_t i = 0; i < idx || cur_node->next_node != NULL; i++) {
        cur_node = cur_node->next_node;
    }
    remove_node(ll, cur_node);
}

void destroy_ll(struct LinkedList *ll)
{
    while(ll->head != NULL) {
        if(ll->head->next_node != NULL) {
            remove_head(ll);
        } else {
            ll->head = NULL;
            free(ll->head);
            ll = NULL;
            break;
        }
    }
}

void print_node(struct Node node)
{
    if(node.prev_node != NULL)
        printf("PREV: %s, %p\n", node.prev_node->value,
               (void *)node.prev_node);
    else
        printf("PREV: NULL, %p\n", (void *)node.prev_node);

    if(node.value != NULL)
        printf("VAL: %s, %p\n", node.value,
               (void *)&node);
    else
        printf("VAL: NULL, %p\n", (void *)&node);

    if(node.next_node != NULL)
        printf("NEXT: %s, %p\n", node.next_node->value,
               (void *)node.next_node);
    else
        printf("NEXT: NULL, %p\n", (void *)node.next_node);


    printf("\n");
}

void print_ll(struct LinkedList ll)
{
    if(ll.head == NULL) {
        puts("List is empty!");
        return;
    }

    struct Node *cur_node = ll.head;
    while(cur_node != NULL) {
        if(cur_node->next_node == NULL) {
            printf("%s\n", cur_node->value);
            break;
        } else {
            printf("%s->", cur_node->value);
            cur_node = cur_node->next_node;
        }
    }
}

void print_ll_detailed(struct LinkedList ll)
{
    if(ll.head == NULL) {
        puts("List is empty.");
        return;
    }

    size_t i = 0;
    struct Node *cur_node = ll.head;
    while(cur_node != NULL) {
        printf("Node %zu:\n", i);
        print_node(*cur_node);
        cur_node = cur_node->next_node;
        i++;
    }
}

void print_head(struct LinkedList ll)
{
    printf("Head is: %s\n", get_head(ll));
}

void print_node_at_index(struct LinkedList ll, size_t idx)
{
    printf("%s\n", get_index(ll, idx));
}

void print_tail(struct LinkedList ll)
{
    printf("Tail is: %s\n", get_tail(ll));
}
