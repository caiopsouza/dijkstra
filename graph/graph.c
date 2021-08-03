#include <stdio.h>
#include <malloc.h>
#include "graph.h"

Graph GRAPH_new(size_t vertices) {
    Graph res = malloc(sizeof(GraphData) + vertices * sizeof(LinkedList));
    res->vertices = vertices;
    res->first = 0;

    for (size_t i = 0; i < vertices; i++)
        res->adjacency[i] = LL_new();

    return res;
}

Graph GRAPH_parse(char *filename) {
    FILE *file = fopen(filename, "r");

    // Header
    size_t nodes = -1, arcs = -1;
    fscanf(file, "NB_NODES%zu\n", &nodes);
    fscanf(file, "NB_ARCS%zu\n", &arcs);
    fscanf(file, "LIST_OF_ARCS COSTS\n");

    Graph res = GRAPH_new(nodes);

    // Body
    for (size_t i = 0; i < arcs; i++) {
        size_t node = -1, neighbor = -1, cost = -1;
        fscanf(file, "%zu %zu %zu", &node, &neighbor, &cost);

        LL_append(res->adjacency[node], neighbor, cost);
        if (i == 0) res->first = node;
    }

    // Footer
    fscanf(file, "END");
    fclose(file);

    return res;
}

void GRAPH_remove_vertex(Graph self, size_t vertex) {
    free(self->adjacency[vertex]);
    self->adjacency[vertex] = LL_new();

    for (size_t i = 0; i < self->vertices; i++) {
        LL_remove_vertex(self->adjacency[i], vertex);
    }
}

void GRAPH_delete(Graph *self) {
    Graph graph = *self;

    for (size_t i = 0; i < graph->vertices; i++)
        LL_delete(&graph->adjacency[i]);

    free(graph);
    *self = NULL;
}