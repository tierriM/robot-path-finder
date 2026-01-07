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

/**
 * Cria uma MinHeap
 */
MinHeap* heapCreate(int capacity);
/**
 * Liberta a memória da MinHeap
 */
void heapFree(MinHeap *heap);

/**
 * Insere um Node na MinHeap
 */
void heapPush(MinHeap *heap, Node node);
/**
 * Remove e retorna o menor Node da MinHeap
 */
Node heapPop(MinHeap *heap);
/**
 * Verifica se a MinHeap está vazia
 */
int heapIsEmpty(MinHeap *heap);

#endif
