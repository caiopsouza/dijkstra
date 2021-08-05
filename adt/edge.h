#ifndef DIJKSTRA_EDGE_H
#define DIJKSTRA_EDGE_H

#include <stddef.h>

typedef struct {
    size_t id;
    size_t cost;
} Edge;

Edge EDGE_new(size_t id, size_t cost);

void EDGE_swap(Edge *a, Edge *b);

#endif //DIJKSTRA_EDGE_H
