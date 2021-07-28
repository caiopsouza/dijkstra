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

void LL_append(LinkedList self, const size_t index, const Cost cost) {
    LinkedListNode node = (LinkedListNode) calloc(1, sizeof(struct LinkedListNodeData));

    node->index = index;
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

void LL_to_array(LinkedList self, ListNode *array) {
    int i = 0;
    for (LL_foreach(self, node)) {
        array[i].index = node->index;
        array[i].cost = node->cost;
        i++;
    }
}