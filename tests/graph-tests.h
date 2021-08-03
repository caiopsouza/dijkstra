#include "cheat.h"
#include "../graph/graph.h"


#define GRAPH_CHECK(adj, expected) \
i = 0; \
for (LL_foreach(adj, actual)) { \
    cheat_assert(actual->vertex == (expected)[i].vertex); \
    cheat_assert(actual->cost == (expected)[i].cost); \
    i++; \
}

#define GRAPH_CHEK_ALL \
size_t i; \
GRAPH_CHECK(graph->adjacency[0], expected0); \
GRAPH_CHECK(graph->adjacency[1], expected1); \
GRAPH_CHECK(graph->adjacency[2], expected2); \
GRAPH_CHECK(graph->adjacency[3], expected3)

CHEAT_TEST(graph_remove_zero, {
    Graph graph = GRAPH_parse("../instances/test_set1/check_v5_s1.dat");
    GRAPH_remove_vertex(graph, 0);

    ListNode expected0[] = {{1, 5},
                            {2, 4},
                            {3, 26},
                            {4, 43}};
    ListNode expected1[] = {{2, 67},
                            {3, 75},
                            {4, 43}};
    ListNode expected2[] = {{1, 67},
                            {3, 38},
                            {4, 48}};
    ListNode expected3[] = {{1, 75},
                            {2, 38},
                            {4, 6}};
    ListNode expected4[] = {{1, 43},
                            {2, 48},
                            {3, 6}};

    GRAPH_CHEK_ALL;

    GRAPH_delete(&graph);
    cheat_assert(graph == NULL);
})

CHEAT_TEST(graph_remove_two, {
    Graph graph = GRAPH_parse("../instances/test_set1/check_v5_s1.dat");
    GRAPH_remove_vertex(graph, 2);

    ListNode expected0[] = {{1, 5},
                            {3, 26},
                            {4, 43}};
    ListNode expected1[] = {{0, 5},
                            {3, 75},
                            {4, 43}};
    ListNode expected2[] = {{0, 4},
                            {1, 67},
                            {3, 38},
                            {4, 48}};
    ListNode expected3[] = {{0, 26},
                            {1, 75},
                            {4, 6}};
    ListNode expected4[] = {{0, 43},
                            {1, 43},
                            {3, 6}};

    GRAPH_CHEK_ALL;

    GRAPH_delete(&graph);
    cheat_assert(graph == NULL);
})
