#include <time.h>
#include <stdio.h>
#include "benchmark.h"

void benchmark(
        char* name,
        void (*dijkstra)(Graph, size_t[]),
        char *instance,
        bool print_result,
        size_t warmup_amount,
        size_t measure_amount
) {

    // Warmup
    for (int i = 0; i < warmup_amount; i++) {
        Graph graph = GRAPH_parse(instance);
        size_t costs[graph->vertices];
        dijkstra(graph, costs);
        GRAPH_delete(&graph);
    }

    double measures[measure_amount];

    // Measure
    for (int i = 0; i < measure_amount; i++) {
        Graph graph = GRAPH_parse(instance);
        size_t costs[graph->vertices];

        clock_t start_time = clock();
        dijkstra(graph, costs);
        measures[i] = (double) (clock() - start_time) / CLOCKS_PER_SEC;

        // Print the last result
        if (print_result && i == measure_amount - 1) {
            printf("Result: %s\n", name);
            for (size_t j = 0; j < graph->vertices; j++)
                printf("%zu %zu\n", j, costs[j]);
            printf("End result: %s\n\n", name);
        }

        GRAPH_delete(&graph);
    }

    printf("Benchmark: %s\n", name);
    for (int i = 0; i < measure_amount; i++)
        printf("Step %d done in %f seconds\n", i, measures[i]);
    printf("End of benchmark: %s\n", name);
}
