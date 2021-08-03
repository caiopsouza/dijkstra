#include <malloc.h>
#include "heap.h"

Heap HEAP_new(size_t capacity) {
    Heap res = malloc(sizeof(HeapData) + capacity * sizeof(size_t));
    res->size = 0;
    return res;
}

void swap(Edge *a, Edge *b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void HEAP_add(Heap self, size_t edge, size_t cost) {
    size_t index = self->size;
    size_t parent = (index - 1) >> 1;

    Edge e = {.id = edge, .cost = cost};
    self->data[index] = e;
    self->size++;

    while (self->data[index].cost < self->data[parent].cost) {
        swap(&self->data[parent], &self->data[index]);
        index = parent;
        parent = (index - 1) >> 1;
    }
}

void HEAP_delete(Heap *self) {
    free(*self);
    *self = NULL;
}