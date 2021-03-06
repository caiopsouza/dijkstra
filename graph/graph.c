#include <stdio.h>
#include <malloc.h>
#include "graph.h"

Graph GRAPH_new(size_t vertices, size_t edges) {
    Graph res = malloc(sizeof(GraphData) + vertices * sizeof(LinkedList));

    res->vertices = vertices;
    res->edges = edges;

    for (size_t i = 0; i < vertices; i++)
        res->adjacency[i] = LL_new();

    return res;
}

Graph GRAPH_parse_test(char *filename) {
    FILE *file = fopen(filename, "r");

    // Header
    size_t nodes = -1, arcs = -1;
    fscanf(file, "NB_NODES%zu\n", &nodes);
    fscanf(file, "NB_ARCS%zu\n", &arcs);
    fscanf(file, "LIST_OF_ARCS COSTS\n");

    Graph res = GRAPH_new(nodes, arcs);

    // Body
    for (size_t i = 0; i < arcs; i++) {
        size_t node = -1, neighbor = -1, cost = -1;
        fscanf(file, "%zu %zu %zu", &node, &neighbor, &cost);

        LL_append(res->adjacency[node], neighbor, cost);
    }

    // Footer
    fscanf(file, "END");
    fclose(file);

    return res;
}

#define LN "%*[^\n]\n"

Graph GRAPH_parse(char *filename) {
    FILE *file = fopen(filename, "r");

    // Header
    size_t nodes = -1, arcs = -1;
    fscanf(file, LN LN LN LN LN "End\n\n" LN); // Skip the first eight lines
    fscanf(file, "Nodes %zu\n", &nodes);
    fscanf(file, "Edges %zu\n", &arcs);

    Graph res = GRAPH_new(nodes, arcs);

    // Body
    for (size_t i = 0; i < arcs; i++) {
        size_t node = -1, neighbor = -1, cost = -1;
        fscanf(file, "E %zu %zu %zu\n", &node, &neighbor, &cost);

        node--;
        neighbor--;

        LL_append(res->adjacency[node], neighbor, cost);
        LL_append(res->adjacency[neighbor], node, cost);
    }

    // Footer
    fscanf(file, "END");
    fclose(file);

    return res;
}

void GRAPH_remove_vertex(Graph self, size_t vertex) {
    for (size_t i = 0; i < self->vertices; i++) {
        LL_remove_vertex(self->adjacency[i], vertex);
    }
}

void GRAPH_delete(Graph *self) {
    Graph graph = *self;

    for (size_t i = 0; i < graph->vertices; i++)
        LL_delete(&graph->adjacency[i]);

#ifndef NO_FREE
    free(graph);
#endif

    *self = NULL;
}