#include "cheat.h"
#include "../abt/linked_list.h"

// Creating and deleting
CHEAT_TEST(list_create_and_delete, {
    LinkedList list = LL_new();
    cheat_assert(list != NULL);

    LL_delete(&list);
    cheat_assert(list == NULL);
})

// Append
CHEAT_TEST(list_append, {
    // Empty list
    LinkedList list = LL_new();
    cheat_assert(LL_len(list) == 0);
    cheat_assert(list->first == NULL);
    cheat_assert(list->last == NULL);

    // First element
    LL_append(list, 10);
    cheat_assert(LL_len(list) == 1);

    cheat_assert(list->first == list->last);
    cheat_assert(list->first->next == NULL);

    cheat_assert(list->first->data == 10);
    cheat_assert(list->last->data == 10);

    cheat_assert(list->last->next == NULL);

    // Second element
    LL_append(list, 24);
    cheat_assert(LL_len(list) == 2);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next == list->last);

    cheat_assert(list->first->data == 10);
    cheat_assert(list->last->data == 24);

    cheat_assert(list->last->next == NULL);

    // Third element
    LL_append(list, 666);
    cheat_assert(LL_len(list) == 3);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next != list->last);
    cheat_assert(list->first->next->next == list->last);

    cheat_assert(list->first->data == 10);
    cheat_assert(list->first->next->data == 24);
    cheat_assert(list->last->data == 666);

    cheat_assert(list->last->next == NULL);

    // Fourth element
    LL_append(list, 42);
    cheat_assert(LL_len(list) == 4);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next != list->last);
    cheat_assert(list->first->next->next != list->last);
    cheat_assert(list->first->next->next->next == list->last);

    cheat_assert(list->first->data == 10);
    cheat_assert(list->first->next->data == 24);
    cheat_assert(list->first->next->next->data == 666);
    cheat_assert(list->last->data == 42);

    cheat_assert(list->last->next == NULL);

    LL_delete(&list);
})

// Iterating empty
CHEAT_TEST(list_iter_empty, {
    LinkedList list = LL_new();

    for (LL_foreach(list, _))
        cheat_assert(false); // Should not happen

    LL_delete(&list);
})

// Iterating multiple values
CHEAT_TEST(list_iter, {
    LinkedList list = LL_new();

    int data[] = {10, 24, 666, 42, 0, 7};

    for (int i = 0; i < 6; i++)
        LL_append(list, data[i]);

    int i = 0;


    for (LL_foreach(list, node)) {
        cheat_assert(node->data == data[i]);
        i++;
    }

    LL_delete(&list);
})