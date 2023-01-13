#include "linked_list.h"


struct Node *create_node(char *value)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->value = malloc(strlen(value) + 1);
    new_node->value = value;
    new_node->next_node = NULL;
    new_node->prev_node = NULL;
    return new_node;
}

struct LinkedList create_list()
{
    struct LinkedList ll = {
        .head = NULL,
        .tail = NULL,
    };

    return ll;
}

struct LinkedList create_list_with_head(char *value)
{
    struct LinkedList ll = {
        .head = NULL,
        .tail = NULL,
    };

    ll.head = create_node(value);

    return ll;
}

void add_new_head(struct LinkedList *ll, char *value)
{
    struct Node *new_node = create_node(value);

    if(ll->head == NULL) {
        ll->head = new_node;
    } else {
        new_node->next_node = ll->head;
        ll->head = new_node;
    }

    assert(ll->head->prev_node == NULL);
    assert(ll->head->value == new_node->value);
}

void add_new_tail(struct LinkedList *ll, char *value)
{
    struct Node *new_node = create_node(value);
    struct Node *cur_node = ll->head;

    if(cur_node == NULL) {
        cur_node = new_node;
    } else {
        while(cur_node->next_node != NULL)
            cur_node = cur_node->next_node;
        cur_node->next_node = new_node;
        new_node->prev_node = cur_node;
        ll->tail = new_node;
    }

    assert(ll->tail->prev_node == cur_node);
    assert(ll->tail->value == new_node->value);
    assert(ll->tail->next_node == NULL);
}

void add_at_index_from_head(struct LinkedList *ll, size_t idx, char *value)
{
    struct Node *new_node = create_node(value);
    struct Node *cur_node = ll->head;

    for(size_t i = 0; i < idx; i++) {
        if(cur_node->next_node != NULL)
            cur_node = cur_node->next_node;
    }

    new_node->prev_node = cur_node->prev_node;
    new_node->next_node = cur_node;
    cur_node->prev_node = new_node;
}

void add_at_index_from_tail(struct LinkedList *ll, size_t idx, char *value)
{
    struct Node *new_node = create_node(value);
    struct Node *cur_node = ll->tail;

    for(size_t i = 0; i < idx; i++) {
        if(cur_node->prev_node != NULL)
            cur_node = cur_node->prev_node;
    }

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
    return ll.head->value;
}

char *get_index(struct LinkedList ll, size_t idx)
{
    struct Node *cur = ll.head;
    for(size_t i = 0; i < idx; i++) {
        if(cur->next_node != NULL) {
            cur = cur->next_node;
        } else {
            printf("Reached end of list! Returning last value in list");
            break;
        }
    }

    return cur->value;
}

char *get_tail(struct LinkedList ll)
{
    return ll.tail->value;
}

void remove_head(struct LinkedList *ll)
{
    if(ll->head == NULL) {
        puts("List is empty!");
    } else {
        struct Node *old_head = ll->head;
        struct Node *new_head = ll->head->next_node;
        ll->head = new_head;
        old_head->next_node = NULL;
        free(old_head);
    }
}

void remove_tail(struct LinkedList *ll)
{
    if(ll->tail == NULL) {
        puts("List is empty!");
    } else {
        struct Node *old_tail = ll->tail;
        struct Node *new_tail = ll->tail->prev_node;
        ll->tail = new_tail;
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

void remove_at_index_from_head(struct LinkedList *ll, size_t idx)
{
    struct Node *cur_node = ll->head;
    for(size_t i = 0; i < idx; i++) {
        if(cur_node->next_node != NULL)
            cur_node = cur_node->next_node;
    }
    remove_node(ll, cur_node);
}

void remove_at_index_from_tail(struct LinkedList *ll, size_t idx)
{
    struct Node *cur_node = ll->tail;
    for(size_t i = 0; i < idx; i++) {
        if(cur_node->prev_node != NULL)
            cur_node = cur_node->prev_node;
    }
    remove_node(ll, cur_node);
}

/* clean up all nodes in list */
void destroy_ll(struct LinkedList *ll)
{
    while(ll->head != NULL) {
        remove_head(ll);
    }
}

void print_node(struct Node node, const char *node_name)
{
    printf("%s: \n", node_name);
    if(node.prev_node == NULL) {
        printf("PREV: NULL, %p\nVAL: %s, %p\nNEXT: %s, %p\n",
            (void *)node.prev_node,
            node.value,
            (void *)&node,
            node.next_node->value,
            (void *)node.next_node);
    } else if(node.value == NULL) {
        printf("PREV: %s, %p\nVAL: NULL, %p\nNEXT: %s, %p\n",
            node.prev_node->value,
            (void *)node.prev_node,
            (void *)&node,
            node.next_node->value,
            (void *)node.next_node);
    } else if(node.next_node == NULL) {
        printf("PREV: %s, %p\nVAL: %s, %p\nNEXT: NULL, %p\n",
            node.prev_node->value,
            (void *)node.prev_node,
            node.value,
            (void *)&node,
            (void *)node.next_node);
    } else {
        printf("PREV: %s, %p\nVAL: %s, %p\nNEXT: %s, %p\n",
            node.prev_node->value,
            (void *)node.prev_node,
            node.value,
            (void *)&node,
            node.next_node->value,
            (void *)node.next_node);
    }
    printf("\n");
}

void print_ll(struct LinkedList ll)
{
    struct Node *cur_node = ll.head;
    while(cur_node != NULL) {
        printf("%s\n", cur_node->value);
        cur_node = cur_node->next_node;
    }
    printf("\n");
}

void print_head(struct LinkedList ll)
{
    printf("Head is: %s\n", ll.head->value);
}

void print_node_at_index(struct LinkedList ll, size_t idx)
{
    struct Node *cur_node = ll.head;
    for(size_t i = 0; i < idx; i++) {
        if(cur_node->next_node != NULL)
            cur_node = cur_node->next_node;
    }
    printf("%s\n", cur_node->value);
}

void print_tail(struct LinkedList ll)
{
    printf("Tail is: %s\n", ll.tail->value);
}
