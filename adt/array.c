#include <malloc.h>
#include "array.h"

Array ARRAY_new(size_t capacity) {
    Array res = malloc(sizeof(ArrayData) + capacity * sizeof(size_t));
    res->size = 0;
    return res;
}

Array ARRAY_init(size_t size, size_t initial_value) {
    Array res = malloc(sizeof(ArrayData) + size * sizeof(size_t));
    res->size = size;

    for (size_t i = 0; i < size; i++)
        res->data[i] = initial_value;

    return res;
}

void ARRAY_add(Array self, size_t dist) {
    self->data[self->size++] = dist;
}

void ARRAY_delete(Array *self) {
    free(*self);
    *self = NULL;
}