#include <malloc.h>
#include "array.h"
#include "data.h"

Array ARRAY_new(size_t capacity) {
    Array res = malloc(sizeof(ArrayData) + capacity * sizeof(Distance));
    res->size = 0;
    return res;
}

void ARRAY_add(Array self, Distance dist) {
    self->data[self->size++] = dist;
}

void ARRAY_delete(Array *self) {
    free(*self);
    *self = NULL;
}