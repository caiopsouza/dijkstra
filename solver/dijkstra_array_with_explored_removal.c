#include "dijkstra_array_with_explored_removal.h"

// Set a vertex as explored
void
set_explored_removal(bool is_explored[], size_t costs[], size_t explored[], size_t *explored_next, size_t vertex,
                     size_t cost) {
    is_explored[vertex] = true;
    costs[vertex] = cost;
    explored[(*explored_next)++] = vertex;
}

// Update the neighbors cost
void update_neighbors_removal(Graph graph, size_t vertex, bool is_explored[], size_t costs[]) {
    size_t cost = costs[vertex];
    LinkedList adjacency = graph->adjacency[vertex];
    LinkedListNode last_neighbor = NULL;

    for (LinkedListNode neighbor = adjacency->first; neighbor;) {
        size_t n_vertex = neighbor->vertex;
        if (is_explored[n_vertex]) {
            LinkedListNode next_neighbor = neighbor->next;
            LL_remove_node(adjacency, last_neighbor, neighbor);
            neighbor = next_neighbor;
            continue;
        }

        last_neighbor = neighbor;
        size_t new_cost = cost + neighbor->cost;

        if (new_cost < costs[n_vertex])
            costs[n_vertex] = new_cost;

        neighbor = neighbor->next;
    }
}

void dijkstra_array_with_explored_removal(Graph graph, size_t costs[]) {
    // Reset costs
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
    set_explored_removal(is_explored, costs, explored, &explored_next, start, 0);
    update_neighbors_removal(graph, start, is_explored, costs);

    while (explored_next < graph->vertices) {
        // Find the smallest cost
        size_t smallest_vertex = SIZE_MAX;
        size_t smallest_cost = SIZE_MAX;
        for (size_t i = 0; i < explored_next; i++) {
            size_t vertex = explored[i];
            size_t vertex_cost = costs[vertex];
            LinkedList adjacency = graph->adjacency[vertex];

            LinkedListNode last_neighbor = NULL;
            for (LinkedListNode neighbor = adjacency->first; neighbor;) {
                if (is_explored[neighbor->vertex]) {
                    LinkedListNode next_neighbor = neighbor->next;
                    LL_remove_node(adjacency, last_neighbor, neighbor);
                    neighbor = next_neighbor;
                    continue;
                }

                last_neighbor = neighbor;
                size_t neighbor_cost = vertex_cost + neighbor->cost;

                if (neighbor_cost < smallest_cost) {
                    smallest_cost = neighbor_cost;
                    smallest_vertex = neighbor->vertex;
                }

                neighbor = neighbor->next;
            }
        }

        // Mark as explored and update neighbors
        set_explored_removal(is_explored, costs, explored, &explored_next, smallest_vertex, smallest_cost);
        update_neighbors_removal(graph, smallest_vertex, is_explored, costs);
    }
}
