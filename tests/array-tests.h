#include "cheat.h"
#include "../adt/array.h"

CHEAT_TEST(array_empty, {
    Array array = ARRAY_new(20);
    cheat_assert(array->size == 0);

    ARRAY_delete(&array);
    cheat_assert(array == NULL);
})

CHEAT_TEST(array_single, {
    Array array = ARRAY_new(20);
    ARRAY_add(array, 7);
    cheat_assert(array->size == 1);
    cheat_assert(array->data[0] == 7);

    ARRAY_delete(&array);
    cheat_assert(array == NULL);
})

CHEAT_TEST(array_multiple, {
    Array array = ARRAY_new(20);

    ARRAY_add(array, 7);
    ARRAY_add(array, 666);
    ARRAY_add(array, 42);

    cheat_assert(array->size == 3);

    cheat_assert(array->data[0] == 7);
    cheat_assert(array->data[1] == 666);
    cheat_assert(array->data[2] == 42);

    ARRAY_delete(&array);
    cheat_assert(array == NULL);
})

CHEAT_TEST(array_init, {
    Array array = ARRAY_init(5, 7);

    cheat_assert(array->size == 5);

    cheat_assert(array->data[0] == 7);
    cheat_assert(array->data[1] == 7);
    cheat_assert(array->data[2] == 7);
    cheat_assert(array->data[3] == 7);
    cheat_assert(array->data[4] == 7);

    ARRAY_delete(&array);
    cheat_assert(array == NULL);
})