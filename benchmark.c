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
#include <sys/resource.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

#endif

void benchmark(
        char *name,
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
    printf("Benchmark: %s\n", name);
    for (int i = 0; i < measure_amount; i++) {

        Graph graph = GRAPH_parse(instance);
        size_t costs[graph->vertices];

        double start_time = get_time();
        //clock_t start_time = clock();
        dijkstra(graph, costs);
        //measures[i] = (double) (clock() - start_time) / CLOCKS_PER_SEC;
        measures[i] = get_time() - start_time;

        // Print the last result
        if (print_result && i == measure_amount - 1) {
            printf("Results:\n", name);
            for (size_t j = 0; j < graph->vertices; j++)
                printf("%zu %zu\n", j, costs[j]);
            printf("End results", name);
        }

        GRAPH_delete(&graph);
    }

    for (int i = 0; i < measure_amount; i++)
        printf("Step %d done in %f seconds\n", i, measures[i]);
    printf("End of benchmark: %s\n\n", name);
}
