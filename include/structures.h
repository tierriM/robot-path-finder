#ifndef STRUCTURES_H
#define STRUCTURES_H

// Ponto x y
typedef struct {
    int x;
    int y;
} Point;

// Nodo para o dijkstra
typedef struct {
    Point pos;
    int dist;
    int visited;
} Node;

// MinHeap para o dijkstra
typedef struct {
    Node *data;
    int size;
    int capacity;
} MinHeap;

// Funções da Heap
MinHeap* heap_create(int capacity);
void heap_free(MinHeap *heap);

void heap_push(MinHeap *heap, Node node);
Node heap_pop(MinHeap *heap);
int heap_is_empty(MinHeap *heap);

#endif
