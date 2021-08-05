#include <stdint.h>
#include <stdio.h>
#include "graph/graph.h"
#include "benchmark.h"
#include "solver/dijkstra_array.h"
#include "solver/dijkstra_heap.h"

typedef struct {
    char *file;

    Graph (*parser)(char *);
} Instance;

static Instance instances[] = {
        {"../instances/ALUE/alue2087.stp",           GRAPH_parse},
        {"../instances/ALUE/alue2105.stp",           GRAPH_parse},
        {"../instances/ALUE/alue3146.stp",           GRAPH_parse},
        {"../instances/ALUE/alue5067.stp",           GRAPH_parse},
        {"../instances/ALUE/alue5345.stp",           GRAPH_parse},
        {"../instances/ALUE/alue5623.stp",           GRAPH_parse},
        {"../instances/ALUE/alue5901.stp",           GRAPH_parse},
        {"../instances/ALUE/alue6179.stp",           GRAPH_parse},
        {"../instances/ALUE/alue6457.stp",           GRAPH_parse},
        {"../instances/ALUE/alue6735.stp",           GRAPH_parse},
        {"../instances/ALUE/alue6951.stp",           GRAPH_parse},
        {"../instances/ALUE/alue7065.stp",           GRAPH_parse},
        {"../instances/ALUE/alue7066.stp",           GRAPH_parse},
        {"../instances/ALUE/alue7080.stp",           GRAPH_parse},
        {"../instances/ALUE/alue7229.stp",           GRAPH_parse},

        {"../instances/ALUT/alut0787.stp",           GRAPH_parse},
        {"../instances/ALUT/alut0805.stp",           GRAPH_parse},
        {"../instances/ALUT/alut1181.stp",           GRAPH_parse},
        {"../instances/ALUT/alut2010.stp",           GRAPH_parse},
        {"../instances/ALUT/alut2288.stp",           GRAPH_parse},
        {"../instances/ALUT/alut2566.stp",           GRAPH_parse},
        {"../instances/ALUT/alut2610.stp",           GRAPH_parse},
        {"../instances/ALUT/alut2625.stp",           GRAPH_parse},
        {"../instances/ALUT/alut2764.stp",           GRAPH_parse},

        {"../instances/DMXA/dmxa0296.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa0368.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa0454.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa0628.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa0734.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa0848.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa0903.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa1010.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa1109.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa1200.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa1304.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa1516.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa1721.stp",           GRAPH_parse},
        {"../instances/DMXA/dmxa1801.stp",           GRAPH_parse},

        {"../instances/test_set1/check_v5_s1.dat",   GRAPH_parse_test},
        {"../instances/test_set1/inst_v100_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v200_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v300_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v400_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v500_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v600_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v700_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v800_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v900_s1.dat",  GRAPH_parse_test},
        {"../instances/test_set1/inst_v1000_s1.dat", GRAPH_parse_test},

        {"../instances/test_set2/check_v5_s2.dat",   GRAPH_parse_test},
        {"../instances/test_set2/inst_v100_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v200_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v300_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v400_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v500_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v600_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v700_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v800_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v900_s2.dat",  GRAPH_parse_test},
        {"../instances/test_set2/inst_v1000_s2.dat", GRAPH_parse_test},

        {NULL, NULL},
};

int main() {
    bool print_result = false;
    size_t warmup_amount = 10;
    size_t measure_amount = 20;

    for (size_t i = 0;; i++) {
        Instance instance = instances[i];
        if (!instance.file)
            break;

        Graph graph = instance.parser(instance.file);

        printf("%s\n", instance.file);

        benchmark(
                "array",
                graph,
                dijkstra_array,
                print_result,
                warmup_amount,
                measure_amount);

        benchmark(
                " heap",
                graph,
                dijkstra_heap,
                print_result,
                warmup_amount,
                measure_amount);

        GRAPH_delete(&graph);
        printf("\n");
    }

    return 0;
}
