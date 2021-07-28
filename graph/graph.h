#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H

#include "../adt/linked_list.h"

typedef struct {
    size_t vertices;
    size_t first;
    LinkedList adjacency[];
} GraphData, *Graph;

Graph GRAPH_new(size_t vertices);

Graph GRAPH_parse(char *filename);

void GRAPH_remove_vertex(Graph self, size_t vertex);

void GRAPH_delete(Graph *self);

#endif //DIJKSTRA_GRAPH_H
