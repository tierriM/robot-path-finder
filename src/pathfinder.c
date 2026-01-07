#include <limits.h>
#include <stdlib.h>
#include "pathfinder.h"

/* Direções: cima, baixo, esquerda, direita */
static const int dx[4] = {-1, 1, 0, 0};
static const int dy[4] = {0, 0, -1, 1};

/**
 * Calcula o caminho mínimo entre start e end usando Dijkstra
 */
int dijkstraPath(Grid *g, Point start, Point end, Point *path, int maxPathLength) {
    int rows = g->rows;
    int cols = g->cols;

    // Criar matriz distâncias
    int **dist = malloc(rows * sizeof(int*));
    Point **parent = malloc(rows * sizeof(Point*));
    for (int i = 0; i < rows; i++) {
        dist[i] = malloc(cols * sizeof(int));
        parent[i] = malloc(cols * sizeof(Point));
        for (int j = 0; j < cols; j++) {
            dist[i][j] = INT_MAX;
            parent[i][j].x = -1;  // valor inválido para indicar "sem pai"
            parent[i][j].y = -1;
        }
    }

    MinHeap *heap = heapCreate(rows * cols);

    Node start_node = {start, 0, 0};
    dist[start.x][start.y] = 0;
    heapPush(heap, start_node);

    int found = 0;

    while (!heapIsEmpty(heap)) {
        Node current = heapPop(heap);
        int x = current.pos.x;
        int y = current.pos.y;

        if (current.dist > dist[x][y])
            continue;

        if (x == end.x && y == end.y) {
            found = 1;
            break;
        }

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (!gridIsWalkable(g, nx, ny))
                continue;

            int new_dist = current.dist + 1;

            if (new_dist < dist[nx][ny]) {
                dist[nx][ny] = new_dist;
                parent[nx][ny] = current.pos;
                Node next = {{nx, ny}, new_dist, 0};
                heapPush(heap, next);
            }
        }
    }

    int pathLength = 0;
    if (found) {
        // Reconstruir caminho do end até start usando parent
        Point cur = end;
        while (!(cur.x == -1 && cur.y == -1) && pathLength < maxPathLength) {
            path[pathLength++] = cur;
            cur = parent[cur.x][cur.y];
        }
        // inverter o caminho para ficar do start até end
        for (int i = 0; i < pathLength / 2; i++) {
            Point temp = path[i];
            path[i] = path[pathLength - 1 - i];
            path[pathLength - 1 - i] = temp;
        }
    }

    // Libertar memória
    for (int i = 0; i < rows; i++) {
        free(dist[i]);
        free(parent[i]);
    }
    free(dist);
    free(parent);
    heapFree(heap);

    if (found)
        return pathLength;
    else
        return 0; // sem caminho
}

/**
 * Calcula as distâncias mínimas desde start até todos os packages não visitados
 */
int dijkstraFindPackages(
    Grid *g,
    Point start,
    Point *packages,
    int numPackages,
    int *visited,
    int *distances
) {
    int rows = g->rows;
    int cols = g->cols;

    /* Inicializar distâncias */
    int **dist = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        dist[i] = malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            dist[i][j] = INT_MAX;
        }
    }

    MinHeap *heap = heapCreate(rows * cols);

    Node start_node = { start, 0, 0 };
    dist[start.x][start.y] = 0;
    heapPush(heap, start_node);

    int found = 0;

    while (!heapIsEmpty(heap) && found < numPackages) {
        Node current = heapPop(heap);
        int x = current.pos.x;
        int y = current.pos.y;

        if (current.dist > dist[x][y])
            continue;

        /* Verificar se é um package não visitado */
        for (int i = 0; i < numPackages; i++) {
            if (!visited[i] &&
                packages[i].x == x &&
                packages[i].y == y) {
                distances[i] = current.dist;
                visited[i] = 1;
                found++;
            }
        }

        /* Explorar vizinhos */
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (!gridIsWalkable(g, nx, ny))
                continue;

            int new_dist = current.dist + 1;

            if (new_dist < dist[nx][ny]) {
                dist[nx][ny] = new_dist;
                Node next = { {nx, ny}, new_dist, 0 };
                heapPush(heap, next);
            }
        }
    }

    /* Libertar memória */
    for (int i = 0; i < rows; i++)
        free(dist[i]);
    free(dist);

    heapFree(heap);

    return found;
}
