#include "cheat.h"
#include "../adt/edge.h"

CHEAT_TEST(edge_new, {
    Edge edge = EDGE_new(2, 3);

    cheat_assert(edge.id == 2);
    cheat_assert(edge.cost == 3);
})

CHEAT_TEST(edge_swap, {
    Edge edge_a = EDGE_new(2, 3);
    Edge edge_b = EDGE_new(7, 9);

    EDGE_swap(&edge_a, &edge_b);

    cheat_assert(edge_a.id == 7);
    cheat_assert(edge_a.cost == 9);

    cheat_assert(edge_b.id == 2);
    cheat_assert(edge_b.cost == 3);
})