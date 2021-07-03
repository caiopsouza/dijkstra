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

void LL_append(LinkedList self, const int data) {
    LinkedListNode node = (LinkedListNode) calloc(1, sizeof(struct LinkedListNodeData));

    node->data = data;
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
