#include "linked_list.h"

int main(void)
{
    struct LinkedList ll = create_list();
    add_new_head(&ll, "Ross");
    add_new_tail(&ll, "Grace");
    add_new_tail(&ll, "Stan");
    add_new_head(&ll, "Matty");

    print_ll(ll);

    destroy_ll(&ll);
    print_ll(ll);
    return 0;
}
