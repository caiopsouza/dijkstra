#include <stdlib.h>
#include <stdint.h>
#include "linked_list.h"

LinkedList LL_new() {
    return calloc(1, sizeof(struct LinkedListData));
}

size_t LL_len(LinkedListRO self) {
    return self->len;
}

void LL_delete(LinkedList *self) {
#ifndef NO_FREE
    LinkedListNode node = (*self)->first;
    while (node) {
        LinkedListNode next_node = node->next;
        free(node);
        node = next_node;
    }

    free(*self);
#endif

    *self = NULL;
}

void LL_append(LinkedList self, const size_t vertex, const size_t cost) {
    LinkedListNode node = (LinkedListNode) calloc(1, sizeof(struct LinkedListNodeData));

    node->vertex = vertex;
    node->cost = cost;
    self->len++;

    if (!self->first) {
        self->first = node;
    } else if (!self->first->next) {
        self->first->next = node;
    } else {
        self->last->next = node;
    }

    self->last = node;
}

LinkedListNode LL_remove_node(LinkedList self, LinkedListNode prev_node, LinkedListNode node) {
    if (node) {
        LinkedListNode next = node->next;

        if (prev_node) prev_node->next = node->next;
        else self->first = node->next;

#ifndef NO_FREE
        free(node);
#endif

        self->len--;

        return next;
    }
    return NULL;
}

void LL_remove_vertex(LinkedList self, size_t vertex) {
    LinkedListNode last_node = NULL;
    LinkedListNode node;

    for (LL_foreach_decl(self, node)) {
        if (node->vertex == vertex) break;
        last_node = node;
    }

    LL_remove_node(self, last_node, node);
}

size_t LL_remove_smallest_by_cost(LinkedList vertices, size_t costs[]) {
    LinkedListNode prev = NULL;
    LinkedListNode prev_smallest = NULL;
    LinkedListNode smallest = NULL;
    size_t min_cost = SIZE_MAX;

    for (LL_foreach(vertices, node)) {
        size_t cost = costs[node->vertex];
        if (cost < min_cost) {
            prev_smallest = prev;
            smallest = node;
            min_cost = cost;
        }

        prev = node;
    }

    size_t res = smallest->vertex;
    LL_remove_node(vertices, prev_smallest, smallest);

    return res;
}
