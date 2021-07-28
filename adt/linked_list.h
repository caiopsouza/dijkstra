#ifndef DIJKSTRA_LINKED_LIST_H
#define DIJKSTRA_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct LinkedListData *LinkedList;
typedef const struct LinkedListData *LinkedListRO;

typedef struct LinkedListNodeData *LinkedListNode;

#define LL_foreach_decl(self, vertex) vertex = (self)->first; vertex; (vertex) = (vertex)->next
#define LL_foreach(self, vertex) LinkedListNode vertex = (self)->first; vertex; (vertex) = (vertex)->next

struct LinkedListData {
    size_t len;

    LinkedListNode first;
    LinkedListNode last;
};

typedef struct {
    size_t vertex;
    size_t cost;
} ListNode;

struct LinkedListNodeData {
    size_t vertex;
    size_t cost;
    LinkedListNode next;
};

LinkedList LL_new();

size_t LL_len(LinkedListRO self);

void LL_delete(LinkedList *list);

void LL_append(LinkedList self, size_t vertex, size_t cost);

void LL_remove_vertex(LinkedList self, size_t vertex);

#endif //DIJKSTRA_LINKED_LIST_H
