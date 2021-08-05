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
    printf("Benchmark %s:", name);
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
        printf(" %f", measures[i]);
    printf("\n");
}
