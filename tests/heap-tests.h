#include "cheat.h"
#include "../adt/heap.h"

#define edge_assert(edge, id_expected, cost_expected) \
    cheat_assert((edge).id == (id_expected)); \
    cheat_assert((edge).cost == (cost_expected))

#define heap_assert(heap, index, id_expected, cost_expected) \
    edge_assert((heap)->data[index], id_expected, cost_expected)

CHEAT_TEST(heap_0, {
    Heap heap = HEAP_new(1000);
    cheat_assert(heap != NULL);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_1, {
    Heap heap = HEAP_new(8);

    HEAP_add(heap, 7, 100);
    heap_assert(heap, 0, 7, 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_2, {
    Heap heap = HEAP_new(1000);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);

    heap_assert(heap, 0, 666, 70);
    heap_assert(heap, 1, 7, 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_3, {
    Heap heap = HEAP_new(1000);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);

    heap_assert(heap, 0, 42, 50);
    heap_assert(heap, 1, 7, 100);
    heap_assert(heap, 2, 666, 70);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_4, {
    Heap heap = HEAP_new(1000);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);

    heap_assert(heap, 0, 42, 50);
    heap_assert(heap, 1, 7, 100);
    heap_assert(heap, 2, 666, 70);
    heap_assert(heap, 3, 1, 125);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_5, {
    Heap heap = HEAP_new(1000);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);
    HEAP_add(heap, 2, 45);

    heap_assert(heap, 0, 2, 45);
    heap_assert(heap, 1, 42, 50);
    heap_assert(heap, 2, 666, 70);
    heap_assert(heap, 3, 1, 125);
    heap_assert(heap, 4, 7, 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_6, {
    Heap heap = HEAP_new(1000);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);
    HEAP_add(heap, 2, 45);
    HEAP_add(heap, 20, 60);

    heap_assert(heap, 0, 2, 45);
    heap_assert(heap, 1, 42, 50);
    heap_assert(heap, 2, 20, 60);
    heap_assert(heap, 3, 1, 125);
    heap_assert(heap, 4, 7, 100);
    heap_assert(heap, 5, 666, 70);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_7, {
    Heap heap = HEAP_new(1000);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);
    HEAP_add(heap, 2, 45);
    HEAP_add(heap, 20, 60);
    HEAP_add(heap, 0, 10);

    heap_assert(heap, 0, 0, 10);
    heap_assert(heap, 1, 42, 50);
    heap_assert(heap, 2, 2, 45);
    heap_assert(heap, 3, 1, 125);
    heap_assert(heap, 4, 7, 100);
    heap_assert(heap, 5, 666, 70);
    heap_assert(heap, 6, 20, 60);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_init, {
    Heap heap = HEAP_init(4);

    heap_assert(heap, 0, 0, SIZE_MAX);
    heap_assert(heap, 1, 1, SIZE_MAX);
    heap_assert(heap, 2, 2, SIZE_MAX);
    heap_assert(heap, 3, 3, SIZE_MAX);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_pop, {
    Heap heap = HEAP_new(1000);
    Edge first;

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);
    HEAP_add(heap, 2, 45);
    HEAP_add(heap, 20, 60);
    HEAP_add(heap, 0, 10);

    heap_assert(heap, 0, 0, 10);
    heap_assert(heap, 1, 42, 50);
    heap_assert(heap, 2, 2, 45);
    heap_assert(heap, 3, 1, 125);
    heap_assert(heap, 4, 7, 100);
    heap_assert(heap, 5, 666, 70);
    heap_assert(heap, 6, 20, 60);

    first = HEAP_pop(heap);
    edge_assert(first, 0, 10);
    heap_assert(heap, 0, 2, 45);
    heap_assert(heap, 1, 42, 50);
    heap_assert(heap, 2, 20, 60);
    heap_assert(heap, 3, 1, 125);
    heap_assert(heap, 4, 7, 100);
    heap_assert(heap, 5, 666, 70);

    first = HEAP_pop(heap);
    edge_assert(first, 2, 45);
    heap_assert(heap, 0, 42, 50);
    heap_assert(heap, 1, 666, 70);
    heap_assert(heap, 2, 20, 60);
    heap_assert(heap, 3, 1, 125);
    heap_assert(heap, 4, 7, 100);

    first = HEAP_pop(heap);
    edge_assert(first, 42, 50);
    heap_assert(heap, 0, 20, 60);
    heap_assert(heap, 1, 666, 70);
    heap_assert(heap, 2, 7, 100);
    heap_assert(heap, 3, 1, 125);

    first = HEAP_pop(heap);
    edge_assert(first, 20, 60);
    heap_assert(heap, 0, 666, 70);
    heap_assert(heap, 1, 1, 125);
    heap_assert(heap, 2, 7, 100);

    first = HEAP_pop(heap);
    edge_assert(first, 666, 70);
    heap_assert(heap, 0, 7, 100);
    heap_assert(heap, 1, 1, 125);

    first = HEAP_pop(heap);
    edge_assert(first, 7, 100);
    heap_assert(heap, 0, 1, 125);

    first = HEAP_pop(heap);
    edge_assert(first, 1, 125);
    cheat_assert(heap->size == 0);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})