#include "cheat.h"

#include "../adt/linked_list.h"

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
    LL_append(list, 10, 21);
    cheat_assert(LL_len(list) == 1);

    cheat_assert(list->first == list->last);
    cheat_assert(list->first->next == NULL);

    cheat_assert(list->first->index == 10);
    cheat_assert(list->first->cost == 21);
    cheat_assert(list->last->index == 10);
    cheat_assert(list->last->cost == 21);

    cheat_assert(list->last->next == NULL);

    // Second element
    LL_append(list, 24, 36);
    cheat_assert(LL_len(list) == 2);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next == list->last);

    cheat_assert(list->first->index == 10);
    cheat_assert(list->first->cost == 21);
    cheat_assert(list->last->index == 24);
    cheat_assert(list->last->cost == 36);

    cheat_assert(list->last->next == NULL);

    // Third element
    LL_append(list, 666, -7);
    cheat_assert(LL_len(list) == 3);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next != list->last);
    cheat_assert(list->first->next->next == list->last);

    cheat_assert(list->first->index == 10);
    cheat_assert(list->first->next->index == 24);
    cheat_assert(list->last->index == 666);
    cheat_assert(list->last->cost == -7);

    cheat_assert(list->last->next == NULL);

    // Fourth element
    LL_append(list, 42, 4);
    cheat_assert(LL_len(list) == 4);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next != list->last);
    cheat_assert(list->first->next->next != list->last);
    cheat_assert(list->first->next->next->next == list->last);

    cheat_assert(list->first->index == 10);
    cheat_assert(list->first->next->index == 24);
    cheat_assert(list->first->next->next->index == 666);
    cheat_assert(list->last->index == 42);
    cheat_assert(list->last->cost == 4);

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

    int index[] = {10, 24, 666, 42, 0, 7};
    int cost[] = {21, 33, 3, 333, 0, 8};

    for (int i = 0; i < 6; i++)
        LL_append(list, index[i], cost[i]);

    int i = 0;
    for (LL_foreach(list, node)) {
        cheat_assert(node->index == index[i]);
        cheat_assert(node->cost == cost[i]);
        i++;
    }

    LL_delete(&list);
})

// To array
CHEAT_TEST(list_to_array, {
    LinkedList list = LL_new();

    int index[] = {10, 24, 666, 42, 0, 7};
    int cost[] = {21, 33, 3, 333, 0, 8};

    for (int i = 0; i < 6; i++)
        LL_append(list, index[i], cost[i]);

    ListNode expected[] = {
            {10,  21},
            {24,  33},
            {666, 3},
            {42,  333},
            {0,   0},
            {7,   8}
    };
    ListNode actual[6];

    LL_to_array(list, actual);

    for (size_t i = 0; i < 6; i++) {
        cheat_assert(actual[i].index == expected[i].index);
        cheat_assert(actual[i].cost == expected[i].cost);
    }

    LL_delete(&list);
})