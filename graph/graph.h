#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H

#include "../adt/linked_list.h"

typedef struct {
    size_t arcs;
    LinkedList adjacency[];
} GraphData, *Graph;

Graph GRAPH_new(size_t size);

Graph GRAPH_parse(char *filename);

#endif //DIJKSTRA_GRAPH_H
