#include "cheat.h"
#include "../graph/graph.h"

#define GRAPH_PARSE_CHECK(adj, expected) \
i = 0; \
for (LL_foreach(adj, actual)) { \
    cheat_assert(actual->vertex == expected[i].vertex); \
    cheat_assert(actual->cost == expected[i].cost); \
    i++; \
}

CHEAT_TEST(graph_parse_check_v5_s1, {
    Graph graph = GRAPH_parse_test("../instances/test_set1/check_v5_s1.dat");

    cheat_assert(graph->vertices == 5);

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

    GRAPH_PARSE_CHECK(graph->adjacency[0], expected0);
    GRAPH_PARSE_CHECK(graph->adjacency[1], expected1);
    GRAPH_PARSE_CHECK(graph->adjacency[2], expected2);
    GRAPH_PARSE_CHECK(graph->adjacency[3], expected3);

    GRAPH_delete(&graph);
    cheat_assert(graph == NULL);
})
