#ifndef DIJKSTRA_HEAP_H
#define DIJKSTRA_HEAP_H

#include <stdio.h>
#include "data.h"

typedef struct{
    size_t size;
    Distance data[];
} HeapData, *Heap;

Heap HEAP_new(size_t capacity);

void HEAP_add(Heap self, Distance dist);

void HEAP_delete(Heap *self);

#endif //DIJKSTRA_HEAP_H
