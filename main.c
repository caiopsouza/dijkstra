#include <stdint.h>
#include <time.h>
#include "graph/graph.h"
#include "adt/array.h"

// Set a vertex as explored
void
set_explored(bool is_explored[], size_t costs[], size_t explored[], size_t *explored_next, size_t vertex, size_t cost) {
    is_explored[vertex] = true;
    costs[vertex] = cost;
    explored[(*explored_next)++] = vertex;
}

// Update the neighbors cost
void update_neighbors(Graph graph, size_t vertex, bool is_explored[], size_t costs[]) {
    size_t cost = costs[vertex];
    LinkedList adjacency = graph->adjacency[vertex];

    for (LL_foreach(adjacency, neighbor)) {
        size_t n_vertex = neighbor->vertex;
        if (is_explored[n_vertex])
            continue;

        size_t new_cost = cost + neighbor->cost;
        if (new_cost < costs[n_vertex])
            costs[n_vertex] = new_cost;
    }
}

// Reference: Algorithm Design by Jon Kleinberg and Eva Tardos. pages 137-138.
int dijkstra(const Graph const graph, size_t costs[]) {
    // Costs and explored
    bool is_explored[graph->vertices];
    for (size_t i = 0; i < graph->vertices; i++) {
        costs[i] = SIZE_MAX;
        is_explored[i] = false;
    }

    // Explored list
    size_t explored[graph->vertices];
    size_t explored_next = 0;

    // Starts with the first on the graph as explored
    size_t start = 0;
    set_explored(is_explored, costs, explored, &explored_next, start, 0);
    update_neighbors(graph, start, is_explored, costs);

    while (explored_next < graph->vertices) {
        // Find the smallest cost
        size_t smallest_vertex = SIZE_MAX;
        size_t smallest_cost = SIZE_MAX;
        for (size_t i = 0; i < explored_next; i++) {
            size_t vertex = explored[i];
            size_t vertex_cost = costs[vertex];
            LinkedList adjacency = graph->adjacency[vertex];

            for (LL_foreach(adjacency, neighbor)) {
                if (is_explored[neighbor->vertex])
                    continue;

                size_t neighbor_cost = vertex_cost + neighbor->cost;
                if (neighbor_cost < smallest_cost) {
                    smallest_cost = neighbor_cost;
                    smallest_vertex = neighbor->vertex;
                }
            }
        }

        // Mark as explored and update neighbors
        set_explored(is_explored, costs, explored, &explored_next, smallest_vertex, smallest_cost);
        update_neighbors(graph, smallest_vertex, is_explored, costs);
    }
}

int main() {
    Graph graph = GRAPH_parse("../instances/test_set1/inst_v1000_s1.dat");
    size_t costs[graph->vertices];

    size_t warmup_times = 0;
    size_t measure_times = 1;

    // Warmup
    for (int i = 0; i < warmup_times; i++)
        dijkstra(graph, costs);

    double measures[measure_times];

    // Measure
    for (int i = 0; i < measure_times; i++) {
        clock_t start_time = clock();
        dijkstra(graph, costs);
        measures[i] = (double) (clock() - start_time) / CLOCKS_PER_SEC;
    }

    for (int i = 0; i < measure_times; i++)
        printf("Step %d done in %f seconds\n", i, measures[i]);

    //for (size_t i = 0; i < graph->vertices; ++i)
    //printf("%zu %zu\n", i, costs[i]);

    GRAPH_delete(&graph);
    return 0;
}
