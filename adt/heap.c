#include <malloc.h>
#include "heap.h"

Heap HEAP_new(size_t capacity) {
    Heap res = malloc(sizeof(HeapData) + capacity * sizeof(size_t));
    res->size = 0;
    return res;
}

void swap(size_t *a, size_t *b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

void HEAP_add(Heap self, size_t dist) {
    size_t index = self->size;
    size_t parent = (index - 1) >> 1;

    self->data[index] = dist;

    while (self->data[index] < self->data[parent]) {
        swap(&self->data[parent], &self->data[index]);
        index = parent;
        parent = (index - 1) >> 1;
    }

    self->size++;
    self->data[index] = dist;
}

void HEAP_delete(Heap *self) {
    free(*self);
    *self = NULL;
}