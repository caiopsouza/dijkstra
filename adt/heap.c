#include <malloc.h>
#include <stdbool.h>
#include "heap.h"

Heap HEAP_new(size_t capacity) {
    Heap res = malloc(sizeof(HeapData) + capacity * sizeof(Edge));
    res->keys = malloc(capacity * sizeof(size_t));
    res->size = 0;

    for (size_t i = 0; i < capacity; i++) {
        Edge e = {.id = 0, .cost = SIZE_MAX};
        res->data[i] = e;
    }

    return res;
}

Heap HEAP_init(size_t size) {
    Heap res = HEAP_new(size);
    res->size = size;

    for (size_t i = 0; i < size; i++) {
        Edge e = {.id = i, .cost = SIZE_MAX};
        res->data[i] = e;
        res->keys[i] = i;
    }

    return res;
}

void heapify(Heap self, size_t index) {
    size_t parent = (index - 1) >> 1;

    while (index > 0 && self->data[index].cost < self->data[parent].cost) {
        self->keys[self->data[parent].id] = index;
        self->keys[self->data[index].id] = parent;

        EDGE_swap(&self->data[parent], &self->data[index]);

        index = parent;
        parent = (index - 1) >> 1;
    }
}

void HEAP_add(Heap self, size_t edge, size_t cost) {
    size_t index = self->size;

    Edge e = {.id = edge, .cost = cost};
    self->data[index] = e;
    self->keys[edge] = index;
    self->size++;

    heapify(self, index);
}

void HEAP_decrease_to(Heap self, size_t vertex, size_t new_cost) {
    size_t index = self->keys[vertex];
    self->data[index].cost = new_cost;
    heapify(self, index);
}

Edge HEAP_pop(Heap self) {
    Edge res = self->data[0];

    self->data[0] = self->data[self->size - 1];

    size_t index = 0;
    while (true) {
        size_t child2 = 2 * (index + 1);
        size_t child1 = child2 - 1;

        if (child1 >= self->size)
            break;

        size_t smallest_child = child1;
        Edge smallest_edge = self->data[smallest_child];
        if (child2 < self->size && self->data[child2].cost < smallest_edge.cost) {
            smallest_child = child2;
            smallest_edge = self->data[child2];
        }

        if (self->data[index].cost < smallest_edge.cost)
            break;

        EDGE_swap(&self->data[index], &self->data[smallest_child]);
        index = smallest_child;
    }

    self->size--;
    return res;
}

void HEAP_delete(Heap *self) {
    free((*self)->keys);
    free(*self);
    *self = NULL;
}