#ifndef DIJKSTRA_LINKED_LIST_H
#define DIJKSTRA_LINKED_LIST_H

#include <stdbool.h>
#include "data.h"

typedef struct LinkedListData *LinkedList;
typedef const struct LinkedListData *LinkedListRO;

typedef struct LinkedListNodeData *LinkedListNode;

#define LL_foreach(self, node) LinkedListNode node = (self)->first; node; (node) = (node)->next

struct LinkedListData {
    size_t len;

    LinkedListNode first;
    LinkedListNode last;
};

typedef struct {
    size_t index;
    Cost cost;
} ListNode;

struct LinkedListNodeData {
    size_t index;
    Cost cost;
    LinkedListNode next;
};

LinkedList LL_new();

size_t LL_len(LinkedListRO self);

void LL_delete(LinkedList *list);

void LL_append(LinkedList self, size_t index, Cost cost);

void LL_to_array(LinkedList self, ListNode *array);

#endif //DIJKSTRA_LINKED_LIST_H
