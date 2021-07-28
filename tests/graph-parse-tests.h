#include "cheat.h"
#include "../graph/graph.h"

CHEAT_TEST(graph_parse_check_v5_s1, {
    Graph graph = GRAPH_parse("../instances/test_set1/check_v5_s1.dat");

    cheat_assert(graph->arcs == 20);

    ListNode actual[4];

    ListNode expected0[] = {{1, 5},
                            {2, 4},
                            {3, 26},
                            {4, 43}};
    ListNode expected1[] = {{0, 5},
                            {2, 67},
                            {3, 75},
                            {4, 43}};
    ListNode expected2[] = {{0, 4},
                            {1, 67},
                            {3, 38},
                            {4, 48}};
    ListNode expected3[] = {{0, 26},
                            {1, 75},
                            {2, 38},
                            {4, 6}};
    ListNode expected4[] = {{0, 43},
                            {1, 43},
                            {2, 48},
                            {3, 6}};

    LL_to_array(graph->adjacency[0], actual);
    for (size_t i = 0; i < 4; i++) {
        cheat_assert(actual[i].index == expected0[i].index);
        cheat_assert(actual[i].cost == expected0[i].cost);
    }

    LL_to_array(graph->adjacency[1], actual);
    for (size_t i = 0; i < 4; i++) {
        cheat_assert(actual[i].index == expected1[i].index);
        cheat_assert(actual[i].cost == expected1[i].cost);
    }

    LL_to_array(graph->adjacency[2], actual);
    for (size_t i = 0; i < 4; i++) {
        cheat_assert(actual[i].index == expected2[i].index);
        cheat_assert(actual[i].cost == expected2[i].cost);
    }

    LL_to_array(graph->adjacency[3], actual);
    for (size_t i = 0; i < 4; i++) {
        cheat_assert(actual[i].index == expected3[i].index);
        cheat_assert(actual[i].cost == expected3[i].cost);
    }

    LL_to_array(graph->adjacency[4], actual);
    for (size_t i = 0; i < 4; i++) {
        cheat_assert(actual[i].index == expected4[i].index);
        cheat_assert(actual[i].cost == expected4[i].cost);
    }

    GRAPH_delete(&graph);
    cheat_assert(graph == NULL);
})
