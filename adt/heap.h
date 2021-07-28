#ifndef DIJKSTRA_HEAP_H
#define DIJKSTRA_HEAP_H

#include <stdio.h>

typedef struct{
    size_t size;
    size_t data[];
} HeapData, *Heap;

Heap HEAP_new(size_t capacity);

void HEAP_add(Heap self, size_t dist);

void HEAP_delete(Heap *self);

#endif //DIJKSTRA_HEAP_H
