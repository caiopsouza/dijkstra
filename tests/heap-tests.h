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

    HEAP_add(heap, 100);
    cheat_assert(heap->data[0] == 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_2, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 100);
    HEAP_add(heap, 70);
    cheat_assert(heap->data[0] == 70);
    cheat_assert(heap->data[1] == 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_3, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 100);
    HEAP_add(heap, 70);
    HEAP_add(heap, 50);
    cheat_assert(heap->data[0] == 50);
    cheat_assert(heap->data[1] == 100);
    cheat_assert(heap->data[2] == 70);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_4, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 100);
    HEAP_add(heap, 70);
    HEAP_add(heap, 50);
    HEAP_add(heap, 125);
    cheat_assert(heap->data[0] == 50);
    cheat_assert(heap->data[1] == 100);
    cheat_assert(heap->data[2] == 70);
    cheat_assert(heap->data[3] == 125);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_5, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 100);
    HEAP_add(heap, 70);
    HEAP_add(heap, 50);
    HEAP_add(heap, 125);
    HEAP_add(heap, 45);
    cheat_assert(heap->data[0] == 45);
    cheat_assert(heap->data[1] == 50);
    cheat_assert(heap->data[2] == 70);
    cheat_assert(heap->data[3] == 125);
    cheat_assert(heap->data[4] == 100);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_6, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 100);
    HEAP_add(heap, 70);
    HEAP_add(heap, 50);
    HEAP_add(heap, 125);
    HEAP_add(heap, 45);
    HEAP_add(heap, 60);
    cheat_assert(heap->data[0] == 45);
    cheat_assert(heap->data[1] == 50);
    cheat_assert(heap->data[2] == 60);
    cheat_assert(heap->data[3] == 125);
    cheat_assert(heap->data[4] == 100);
    cheat_assert(heap->data[5] == 70);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})

CHEAT_TEST(heap_7, {
    Heap heap = HEAP_new(20);

    HEAP_add(heap, 100);
    HEAP_add(heap, 70);
    HEAP_add(heap, 50);
    HEAP_add(heap, 125);
    HEAP_add(heap, 45);
    HEAP_add(heap, 60);
    HEAP_add(heap, 10);
    cheat_assert(heap->data[0] == 10);
    cheat_assert(heap->data[1] == 50);
    cheat_assert(heap->data[2] == 45);
    cheat_assert(heap->data[3] == 125);
    cheat_assert(heap->data[4] == 100);
    cheat_assert(heap->data[5] == 70);
    cheat_assert(heap->data[6] == 60);

    HEAP_delete(&heap);
    cheat_assert(heap == NULL);
})
