#include "graph/graph.h"
#include "adt/array.h"

// Reference: Algorithm Design by Jon Kleinberg and Eva Tardos. pages 137-138.
int main() {
    Graph graph = GRAPH_parse("../instances/test_set1/check_v5_s1.dat");

    Array explored = ARRAY_new(graph->vertices);
    Array distances = ARRAY_new(graph->vertices);

    size_t exploring = graph->first;
    size_t distance = 0;
    do {
        ARRAY_add(explored, exploring);
        ARRAY_add(distances, distance);
        GRAPH_remove_vertex(graph, exploring);
    } while (explored->size < graph->vertices);

    GRAPH_delete(&graph);
    return 0;
}
