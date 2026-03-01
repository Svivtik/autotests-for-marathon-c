#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "t00/list.h" // Assuming list.h is same everywhere

// Prototypes
t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_back(t_list **list);
void mx_pop_front(t_list **list);
int mx_list_size(t_list *list);
void mx_push_index(t_list **list, void *data, int index);
void mx_pop_index(t_list **list, int index);
void mx_clear_list(t_list **list);
void mx_foreach_list(t_list *list, void (*f)(t_list *node));
t_list *mx_sort_list(t_list *list, bool (*cmp)(void *, void *));
void mx_del_node_if(t_list **list, void *del_data, bool (*cmp)(void *, void *));

// Helpers
void print_node(t_list *node) {
    if (node) printf("[%s] -> ", (char *)node->data);
}
void print_list(t_list *list) {
    if (!list) printf("(null)\n");
    while (list) {
        print_node(list);
        list = list->next;
    }
    printf("NULL\n");
}
bool cmp_str(void *a, void *b) {
    return strcmp((char *)a, (char *)b) > 0; // for sort (asc)
}
bool cmp_eq(void *a, void *b) {
    return strcmp((char *)a, (char *)b) == 0; // for del (equal)
}

int main(void) {
    t_list *head = NULL;

    printf("=== T00-T02: Create & Push ===\n");
    mx_push_front(&head, "World");
    mx_push_front(&head, "Hello");
    mx_push_back(&head, "!");
    print_list(head); // Hello -> World -> ! -> NULL

    printf("\n=== T06: Push Index (1, 'Beautiful') ===\n");
    mx_push_index(&head, "Beautiful", 1);
    print_list(head); // Hello -> Beautiful -> World -> ! -> NULL

    printf("\n=== T05: Size: %d ===\n", mx_list_size(head));

    printf("\n=== T10: Sort ===\n");
    mx_sort_list(head, cmp_str);
    print_list(head); // ! -> Beautiful -> Hello -> World -> NULL

    printf("\n=== T03/T04/T07: Pop operations ===\n");
    mx_pop_back(&head); // Remove World
    mx_pop_front(&head); // Remove !
    mx_pop_index(&head, 0); // Remove Beautiful
    print_list(head); // Hello -> NULL

    printf("\n=== T11: Del Node If 'Hello' ===\n");
    mx_del_node_if(&head, "Hello", cmp_eq);
    print_list(head); // (null)

    return 0;
}
