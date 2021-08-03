#include "cheat.h"
#include "../adt/heap.h"

CHEAT_TEST(heap_0, {
    Heap heap = HEAP_new(20);
    cheat_assert(heap != NULL);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_1, {
    Heap heap = HEAP_new(6);

    HEAP_add(heap, 7, 100);
    cheat_assert(heap->data[0].id == 7);
    cheat_assert(heap->data[0].cost == 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_2, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);

    cheat_assert(heap->data[0].id == 666);
    cheat_assert(heap->data[0].cost == 70);

    cheat_assert(heap->data[1].id == 7);
    cheat_assert(heap->data[1].cost == 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_3, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);

    cheat_assert(heap->data[0].id == 42);
    cheat_assert(heap->data[0].cost == 50);

    cheat_assert(heap->data[1].id == 7);
    cheat_assert(heap->data[1].cost == 100);

    cheat_assert(heap->data[2].id == 666);
    cheat_assert(heap->data[2].cost == 70);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_4, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);

    cheat_assert(heap->data[0].id == 42);
    cheat_assert(heap->data[0].cost == 50);

    cheat_assert(heap->data[1].id == 7);
    cheat_assert(heap->data[1].cost == 100);

    cheat_assert(heap->data[2].id == 666);
    cheat_assert(heap->data[2].cost == 70);

    cheat_assert(heap->data[3].id == 1);
    cheat_assert(heap->data[3].cost == 125);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_5, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);
    HEAP_add(heap, 2, 45);

    cheat_assert(heap->data[0].id == 2);
    cheat_assert(heap->data[0].cost == 45);

    cheat_assert(heap->data[1].id == 42);
    cheat_assert(heap->data[1].cost == 50);

    cheat_assert(heap->data[2].id == 666);
    cheat_assert(heap->data[2].cost == 70);

    cheat_assert(heap->data[3].id == 1);
    cheat_assert(heap->data[3].cost == 125);

    cheat_assert(heap->data[4].id == 7);
    cheat_assert(heap->data[4].cost == 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_6, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);
    HEAP_add(heap, 2, 45);
    HEAP_add(heap, 20, 60);

    cheat_assert(heap->data[0].id == 2);
    cheat_assert(heap->data[0].cost == 45);

    cheat_assert(heap->data[1].id == 42);
    cheat_assert(heap->data[1].cost == 50);

    cheat_assert(heap->data[2].id == 20);
    cheat_assert(heap->data[2].cost == 60);

    cheat_assert(heap->data[3].id == 1);
    cheat_assert(heap->data[3].cost == 125);

    cheat_assert(heap->data[4].id == 7);
    cheat_assert(heap->data[4].cost == 100);

    cheat_assert(heap->data[5].id == 666);
    cheat_assert(heap->data[5].cost == 70);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_7, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 7, 100);
    HEAP_add(heap, 666, 70);
    HEAP_add(heap, 42, 50);
    HEAP_add(heap, 1, 125);
    HEAP_add(heap, 2, 45);
    HEAP_add(heap, 20, 60);
    HEAP_add(heap, 0, 10);

    cheat_assert(heap->data[0].id == 0);
    cheat_assert(heap->data[0].cost == 10);

    cheat_assert(heap->data[1].id == 42);
    cheat_assert(heap->data[1].cost == 50);

    cheat_assert(heap->data[2].id == 2);
    cheat_assert(heap->data[2].cost == 45);

    cheat_assert(heap->data[3].id == 1);
    cheat_assert(heap->data[3].cost == 125);

    cheat_assert(heap->data[4].id == 7);
    cheat_assert(heap->data[4].cost == 100);

    cheat_assert(heap->data[5].id == 666);
    cheat_assert(heap->data[5].cost == 70);

    cheat_assert(heap->data[6].id == 20);
    cheat_assert(heap->data[6].cost == 60);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})
