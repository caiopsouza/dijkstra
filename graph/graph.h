#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H

#include "../adt/linked_list.h"

typedef struct {
    size_t nodes;
    size_t arcs;
    size_t first;
    LinkedList adjacency[];
} GraphData, *Graph;

Graph GRAPH_new(size_t size);

Graph GRAPH_parse(char *filename);

void GRAPH_delete(Graph *self);

#endif //DIJKSTRA_GRAPH_H
