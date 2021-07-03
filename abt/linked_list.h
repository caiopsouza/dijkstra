#ifndef DIJKSTRA_LINKED_LIST_H
#define DIJKSTRA_LINKED_LIST_H

#include <stdbool.h>

typedef struct LinkedListData *LinkedList;
typedef const struct LinkedListData *LinkedListRO;

typedef struct LinkedListNodeData *LinkedListNode;

#define LL_foreach(self, node) LinkedListNode node = (self)->first; node; (node) = (node)->next

struct LinkedListData {
    size_t len;

    LinkedListNode first;
    LinkedListNode last;
};

struct LinkedListNodeData {
    int data;
    LinkedListNode next;
};

LinkedList LL_new();

size_t LL_len(LinkedListRO self);

void LL_delete(LinkedList *list);

void LL_append(LinkedList self, int data);

#endif //DIJKSTRA_LINKED_LIST_H
