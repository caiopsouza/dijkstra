#include <stdio.h>
#include <malloc.h>
#include "graph.h"

Graph GRAPH_new(size_t arcs) {
    Graph res = malloc(sizeof(GraphData) + arcs * sizeof(LinkedList));
    res->arcs = arcs;

    for (size_t i = 0; i < arcs; i++)
        res->adjacency[i] = LL_new();

    return res;
}

Graph GRAPH_parse(char *filename) {
    FILE *file = fopen(filename, "r");

    // Cabeçalho
    size_t nodes = -1, arcs = -1;
    fscanf(file, "NB_NODES%zu\n", &nodes);
    fscanf(file, "NB_ARCS%zu\n", &arcs);
    fscanf(file, "LIST_OF_ARCS COSTS\n");

    Graph res = GRAPH_new(arcs);

    // Corpo
    for (size_t i = 0; i < arcs; i++) {
        size_t node = -1, neighbor = -1;
        unsigned int cost = -1;
        fscanf(file, "%zu %zu %u", &node, &neighbor, &cost);
        LL_append(res->adjacency[node], neighbor, cost);
    }

    // Rodapé
    fscanf(file, "END");
    return res;
}