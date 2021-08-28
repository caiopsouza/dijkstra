#include <time.h>
#include <stdio.h>
#include "benchmark.h"

#ifdef WIN32

#include <windows.h>

double get_time() {
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double) t.QuadPart / (double) f.QuadPart;
}

#else

#include <sys/time.h>

double get_time() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (double) t.tv_sec + 1.0e-9 * t.tv_nsec;
}

#endif

void benchmark(
        char *name,
        Graph graph,
        void (*dijkstra)(Graph, size_t[]),
        bool print_result,
        size_t warmup_amount,
        size_t measure_amount
) {
    size_t costs[graph->vertices];

    // Warmup
    for (int i = 0; i < warmup_amount; i++)
        dijkstra(graph, costs);

    double measures[measure_amount];

    // Measure
    printf("Benchmark %s (%zu, %zu):", name, graph->vertices, graph->edges);
    for (int i = 0; i < measure_amount; i++) {
        double start_time = get_time();
        dijkstra(graph, costs);
        measures[i] = get_time() - start_time;
    }

    for (int i = 0; i < measure_amount; i++)
        printf(" %2.8f", measures[i]);
    printf("\n");
}

void benchmark2(
        char *name,
        Graph graph,
        void (*dijkstra)(Graph, size_t[]),
        bool print_result,
        size_t warmup_amount,
        size_t measure_amount
        ) {
    size_t costs[graph->vertices];

    // Warmup
    for (int i = 0; i < warmup_amount; i++)
        dijkstra(graph, costs);

    double measures[measure_amount];

    // Measure
    printf("Benchmark %s (%zu, %zu):", name, graph->vertices, graph->edges);
    for (int i = 0; i < measure_amount; i++) {
        double start_time = get_time();
        dijkstra(graph, costs);
        measures[i] = get_time() - start_time;

        // Print the last result
        if (print_result && i == measure_amount - 1) {
            printf("Results:\n");
            for (size_t j = 0; j < graph->vertices; j++)
                printf("%zu %zu\n", j, costs[j]);
            printf("End results");
        }
    }

    for (int i = 0; i < measure_amount; i++)
        printf(" %2.8f", measures[i]);
    printf("\n");
}