#include <stdio.h>
#include "dijkstra_array.h"

void dijkstra_array(Graph graph, size_t costs[]) {
    LinkedList unexplored = LL_new(graph->vertices);

    // Initialize the unexplored to every vertex and the costs to max
    for (size_t i = 0; i < graph->vertices; i++) {
        costs[i] = SIZE_MAX;
        LL_append(unexplored, i, SIZE_MAX);
    }

    // Starts with the first on the graph as explored
    costs[0] = 0;

    while (unexplored->len) {
        size_t smallest_vertex = LL_remove_smallest_by_cost(unexplored, costs);

        LinkedList adjacency = graph->adjacency[smallest_vertex];
        size_t current_cost = costs[smallest_vertex];

        for (LL_foreach(adjacency, neighbor)) {
            size_t n_vertex = neighbor->vertex;
            size_t new_cost = current_cost + neighbor->cost;

            if (new_cost < costs[n_vertex]) {
                costs[n_vertex] = new_cost;
            }
        }
    }

    LL_delete(&unexplored);
}
