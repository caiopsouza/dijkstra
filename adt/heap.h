#ifndef DIJKSTRA_HEAP_H
#define DIJKSTRA_HEAP_H

#include <stdio.h>
#include "edge.h"

typedef struct{
    size_t size;
    Edge data[];
} HeapData, *Heap;

Heap HEAP_new(size_t capacity);

void HEAP_add(Heap self, size_t edge, size_t cost);

void HEAP_delete(Heap *self);

#endif //DIJKSTRA_HEAP_H
