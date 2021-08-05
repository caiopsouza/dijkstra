#include <stdint.h>
#include "graph/graph.h"
#include "benchmark.h"
#include "solver/dijkstra_array.h"
#include "solver/dijkstra_heap.h"

int main() {
    char *instance = "../instances/test_set1/inst_v1000_s1.dat";
    bool print_result = false;
    size_t warmup_amount = 5;
    size_t measure_amount = 10;

    benchmark(
            "costs in array",
            dijkstra_array,
            instance,
            print_result,
            warmup_amount,
            measure_amount);

    benchmark(
            "costs in heap",
            dijkstra_heap,
            instance,
            print_result,
            warmup_amount,
            measure_amount);

    return 0;
}
