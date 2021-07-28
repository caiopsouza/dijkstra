#include <malloc.h>
#include "array.h"

Array ARRAY_new(size_t capacity) {
    Array res = malloc(sizeof(ArrayData) + capacity * sizeof(size_t));
    res->size = 0;
    return res;
}

void ARRAY_add(Array self, size_t dist) {
    self->data[self->size++] = dist;
}

void ARRAY_delete(Array *self) {
    free(*self);
    *self = NULL;
}