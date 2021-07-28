#ifndef DIJKSTRA_ARRAY_H
#define DIJKSTRA_ARRAY_H

#include <stdio.h>
#include "data.h"

typedef struct {
    size_t size;
    Distance data[];
} ArrayData, *Array;

Array ARRAY_new(size_t capacity);

void ARRAY_add(Array self, Distance dist);

void ARRAY_delete(Array *self);

#endif //DIJKSTRA_ARRAY_H
