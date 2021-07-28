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

    cheat_assert(list->first->vertex == 10);
    cheat_assert(list->first->cost == 21);
    cheat_assert(list->last->vertex == 10);
    cheat_assert(list->last->cost == 21);

    cheat_assert(list->last->next == NULL);

    // Second element
    LL_append(list, 24, 36);
    cheat_assert(LL_len(list) == 2);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next == list->last);

    cheat_assert(list->first->vertex == 10);
    cheat_assert(list->first->cost == 21);
    cheat_assert(list->last->vertex == 24);
    cheat_assert(list->last->cost == 36);

    cheat_assert(list->last->next == NULL);

    // Third element
    LL_append(list, 666, -7);
    cheat_assert(LL_len(list) == 3);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next != list->last);
    cheat_assert(list->first->next->next == list->last);

    cheat_assert(list->first->vertex == 10);
    cheat_assert(list->first->next->vertex == 24);
    cheat_assert(list->last->vertex == 666);
    cheat_assert(list->last->cost == -7);

    cheat_assert(list->last->next == NULL);

    // Fourth element
    LL_append(list, 42, 4);
    cheat_assert(LL_len(list) == 4);

    cheat_assert(list->first != list->last);
    cheat_assert(list->first->next != list->last);
    cheat_assert(list->first->next->next != list->last);
    cheat_assert(list->first->next->next->next == list->last);

    cheat_assert(list->first->vertex == 10);
    cheat_assert(list->first->next->vertex == 24);
    cheat_assert(list->first->next->next->vertex == 666);
    cheat_assert(list->last->vertex == 42);
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

    int nodes[] = {10, 24, 666, 42, 0, 7};
    int cost[] = {21, 33, 3, 333, 0, 8};

    for (int i = 0; i < 6; i++)
        LL_append(list, nodes[i], cost[i]);

    int i = 0;
    for (LL_foreach(list, node)) {
        cheat_assert(node->vertex == nodes[i]);
        cheat_assert(node->cost == cost[i]);
        i++;
    }

    LL_delete(&list);
})

#define PREPARE_LIST(list) \
int nodes[] = {10, 24, 666, 42, 0, 7}; \
int cost[] = {21, 33, 3, 333, 0, 8}; \
for (int i = 0; i < 6; i++) \
    LL_append((list), nodes[i], cost[i]);

#define CHECK_LIST(list, expected_nodes, expected_cost) \
int i = 0; \
for (LL_foreach((list), node)) { \
    cheat_assert(node->vertex == (expected_nodes)[i]); \
    cheat_assert(node->cost == (expected_cost)[i]); \
    i++; \
}

// Remove vertex
CHEAT_TEST(list_remove_empty, {
    LinkedList list = LL_new();
    LL_remove_vertex(list, 1);
    for (LL_foreach((list), node))
        cheat_assert(false); // Shouldn't happen
    LL_delete(&list);
})

CHEAT_TEST(list_remove_single, {
    LinkedList list = LL_new();
    LL_append(list, 1, 2);
    LL_remove_vertex(list, 1);
    for (LL_foreach((list), node))
        cheat_assert(false); // Shouldn't happen
    LL_delete(&list);
})

CHEAT_TEST(list_remove_first, {
    LinkedList list = LL_new();
    PREPARE_LIST(list);

    LL_remove_vertex(list, 10);

    int expected_nodes[] = {24, 666, 42, 0, 7};
    int expected_cost[] = {33, 3, 333, 0, 8};
    CHECK_LIST(list, expected_nodes, expected_cost);

    LL_delete(&list);
})

CHEAT_TEST(list_remove_middle, {
    LinkedList list = LL_new();
    PREPARE_LIST(list);

    LL_remove_vertex(list, 42);

    int expected_nodes[] = {10, 24, 666, 0, 7};
    int expected_cost[] = {21, 33, 3, 0, 8};
    CHECK_LIST(list, expected_nodes, expected_cost);

    LL_delete(&list);
})

CHEAT_TEST(list_remove_last, {
    LinkedList list = LL_new();
    PREPARE_LIST(list);

    LL_remove_vertex(list, 7);

    int expected_nodes[] = {10, 24, 666, 42, 0};
    int expected_cost[] = {21, 33, 3, 333, 0};
    CHECK_LIST(list, expected_nodes, expected_cost);

    LL_delete(&list);
})
