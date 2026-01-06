#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

// Auxiliares
static void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// Heap
MinHeap* heap_create(int capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    if (!heap) return NULL;

    heap->data = malloc(sizeof(Node) * capacity);
    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

void heap_free(MinHeap *heap) {
    if (!heap) return;
    free(heap->data);
    free(heap);
}

int heap_is_empty(MinHeap *heap) {
    return heap->size == 0;
}

void heap_push(MinHeap *heap, Node node) {
    if (heap->size >= heap->capacity) return;

    int i = heap->size++;
    heap->data[i] = node;

    /* heapify up */
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].dist <= heap->data[i].dist)
            break;

        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

Node heap_pop(MinHeap *heap) {
    Node min = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    int i = 0;

    /* heapify down */
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size &&
            heap->data[left].dist < heap->data[smallest].dist)
            smallest = left;

        if (right < heap->size &&
            heap->data[right].dist < heap->data[smallest].dist)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }

    return min;
}
