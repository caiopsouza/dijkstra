#include "edge.h"

Edge EDGE_new(size_t id, size_t cost) {
    Edge res = {.id = id, .cost = cost};
    return res;
}

inline void EDGE_swap(Edge *a, Edge *b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}