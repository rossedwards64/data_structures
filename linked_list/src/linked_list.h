#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARS_LEN 32


struct Node {
    char *value;
    struct Node *next_node;
    struct Node *prev_node;
};

struct LinkedList {
    struct Node *head;
    struct Node *tail;
};

struct Node *create_node(char *value);
struct LinkedList create_list();
struct LinkedList create_list_with_head(char *value);

void add_new_head(struct LinkedList *ll, char *value);
void add_new_tail(struct LinkedList *ll, char *value);
void add_at_index_from_head(struct LinkedList *ll, size_t idx, char *value);
void add_at_index_from_tail(struct LinkedList *ll, size_t idx, char *value);

bool is_empty(struct LinkedList ll);

char *get_head(struct LinkedList ll);
char *get_index(struct LinkedList ll, size_t idx);
char *get_tail(struct LinkedList ll);

void remove_head(struct LinkedList *ll);
void remove_tail(struct LinkedList *ll);
void remove_node(struct LinkedList *ll, struct Node *node);
void remove_at_index_from_head(struct LinkedList *ll, size_t idx);
void remove_at_index_from_tail(struct LinkedList *ll, size_t idx);
void destroy_ll(struct LinkedList *ll);

void print_node(struct Node node, const char *node_name);
void print_ll(struct LinkedList ll);
void print_head(struct LinkedList ll);
void print_node_at_index(struct LinkedList ll, size_t idx);
void print_tail(struct LinkedList ll);

#endif // LINKED_LIST_H_
