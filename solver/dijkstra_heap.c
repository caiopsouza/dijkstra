#include "dijkstra_heap.h"
#include "../adt/heap.h"

void dijkstra_heap(Graph graph, size_t costs[]) {
    Heap explored = HEAP_new(graph->vertices);

    // Initialize the unexplored to every vertex and the costs to max
    for (size_t i = 0; i < graph->vertices; i++)
        costs[i] = SIZE_MAX;

    // Starts with the first on the graph as explored
    costs[0] = 0;
    HEAP_add(explored, 0, 0);

    while (explored->size) {
        Edge smallest = HEAP_pop(explored);
        size_t smallest_vertex = smallest.id;

        LinkedList adjacency = graph->adjacency[smallest_vertex];
        size_t current_cost = costs[smallest_vertex];

        for (LL_foreach(adjacency, neighbor)) {
            size_t n_vertex = neighbor->vertex;
            size_t new_cost = current_cost + neighbor->cost;

            if (new_cost < costs[n_vertex]) {
                if (costs[n_vertex] == SIZE_MAX)
                    HEAP_add(explored, n_vertex, new_cost);
                else
                    HEAP_decrease_to(explored, n_vertex, new_cost);

                costs[n_vertex] = new_cost;
            }
        }
    }

    HEAP_delete(&explored);
}