#include <stdlib.h>
#include "linked_list.h"

LinkedList LL_new() {
    return calloc(1, sizeof(struct LinkedListData));
}

size_t LL_len(LinkedListRO self) {
    return self->len;
}

void LL_delete(LinkedList *self) {
    LinkedListNode node = (*self)->first;
    while (node) {
        LinkedListNode next_node = node->next;
        free(node);
        node = next_node;
    }

    free(*self);
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

void LL_remove_vertex(LinkedList self, size_t vertex) {
    LinkedListNode last_node = NULL;
    LinkedListNode node;

    for (LL_foreach_decl(self, node)) {
        if (node->vertex == vertex) break;
        last_node = node;
    }

    if (node) {
        if (last_node) last_node->next = node->next;
        else self->first = node->next;
        free(node);
    }
}

ListNode LL_smallest_cost(LinkedList self) {

}