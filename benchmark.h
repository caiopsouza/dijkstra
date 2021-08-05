#ifndef DIJKSTRA_BENCHMARK_H
#define DIJKSTRA_BENCHMARK_H

#include <stdbool.h>
#include "graph/graph.h"

void benchmark(
        char *name,
        Graph graph,
        void (*dijkstra)(Graph, size_t[]),
        bool print_result,
        size_t warmup_amount,
        size_t measure_amount
);

#endif //DIJKSTRA_BENCHMARK_H
