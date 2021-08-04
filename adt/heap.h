#ifndef DIJKSTRA_HEAP_H
#define DIJKSTRA_HEAP_H

#include <stdio.h>
#include "edge.h"

typedef struct {
    size_t size;
    Edge data[];
} HeapData, *Heap;

Heap HEAP_new(size_t capacity);

Heap HEAP_init(size_t size);

void HEAP_add(Heap self, size_t edge, size_t cost);

Edge HEAP_pop(Heap self);

void HEAP_delete(Heap *self);

#endif //DIJKSTRA_HEAP_H
