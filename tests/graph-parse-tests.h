#include "cheat.h"
#include "../graph/graph.h"

CHEAT_TEST(graph_parse_check_v5_s1, {
    Graph graph = GRAPH_parse("../instances/test_set1/check_v5_s1.dat");

    cheat_assert(graph->nodes == 5);
    cheat_assert(graph->arcs == 20);
    cheat_assert(graph->first == 1);

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

    size_t i;

    i = 0;
    for (LL_foreach(graph->adjacency[0], actual)) {
        cheat_assert(actual->vertex == expected0[i].vertex);
        cheat_assert(actual->cost == expected0[i].cost);
        i++;
    }

    i = 0;
    for (LL_foreach(graph->adjacency[1], actual)) {
        cheat_assert(actual->vertex == expected1[i].vertex);
        cheat_assert(actual->cost == expected1[i].cost);
        i++;
    }

    i = 0;
    for (LL_foreach(graph->adjacency[2], actual)) {
        cheat_assert(actual->vertex == expected2[i].vertex);
        cheat_assert(actual->cost == expected2[i].cost);
        i++;
    }

    i = 0;
    for (LL_foreach(graph->adjacency[3], actual)) {
        cheat_assert(actual->vertex == expected3[i].vertex);
        cheat_assert(actual->cost == expected3[i].cost);
        i++;
    }

    i = 0;
    for (LL_foreach(graph->adjacency[4], actual)) {
        cheat_assert(actual->vertex == expected4[i].vertex);
        cheat_assert(actual->cost == expected4[i].cost);
        i++;
    }

    GRAPH_delete(&graph);
    cheat_assert(graph == NULL);
})
