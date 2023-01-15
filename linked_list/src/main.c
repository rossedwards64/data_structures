#include "linked_list.h"


int main(void)
{
    struct LinkedList *ll = create_list();
    add_new_head(ll, "Dog");
    add_new_tail(ll, "Cat");
    add_new_tail(ll, "Monkey");
    add_new_head(ll, "Armadillo");
    add_at_index(ll, 1, "Fox");
    add_at_index(ll, 1, "Penguin");

    print_ll(*ll);

    remove_head(ll);
    add_new_head(ll, "Rabbit");
    add_at_index(ll, 4, "Tardigrade");
    remove_tail(ll);

    print_ll(*ll);
    destroy_ll(ll);
    print_ll(*ll);
    return 0;
}
