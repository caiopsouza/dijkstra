#include <stdint.h>
#include "graph/graph.h"
#include "benchmark.h"
#include "solver/dijkstra_array_with_explored_removal.h"
#include "solver/dijkstra_array_with_explored_marked.h"

int main() {
    char *instance = "../instances/test_set1/inst_v1000_s1.dat";
    bool print_result = true;
    size_t warmup_amount = 0;
    size_t measure_amount = 1;

    benchmark(
            "costs in array with explored marked",
            dijkstra_array_with_explored_marked,
            instance,
            print_result,
            warmup_amount,
            measure_amount);

    benchmark(
            "costs in array with explored removal",
            dijkstra_array_with_explored_removal,
            instance,
            print_result,
            warmup_amount,
            measure_amount);

    return 0;
}
