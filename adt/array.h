#ifndef DIJKSTRA_ARRAY_H
#define DIJKSTRA_ARRAY_H

#include <stdio.h>

typedef struct {
    size_t size;
    size_t data[];
} ArrayData, *Array;

Array ARRAY_new(size_t capacity);

Array ARRAY_init(size_t size, size_t initial_value);

void ARRAY_add(Array self, size_t dist);

void ARRAY_delete(Array *self);

#endif //DIJKSTRA_ARRAY_H
