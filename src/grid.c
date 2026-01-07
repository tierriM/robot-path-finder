#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

/**
 * Cria uma nova grid
 */
Grid* gridCreate(int rows, int cols) {
    Grid *g = malloc(sizeof(Grid));
    if (!g) return NULL;

    g->rows = rows;
    g->cols = cols;

    g->cells = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        g->cells[i] = malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            g->cells[i][j] = CELL_EMPTY;
        }
    }

    return g;
}

/**
 * Liberta a memória da grid
 */
void gridFree(Grid *g) {
    if (!g) return;

    for (int i = 0; i < g->rows; i++) {
        free(g->cells[i]);
    }
    free(g->cells);
    free(g);
}

/**
 * Verifica se a posição é válida na grid
 */
int gridIsValid(Grid *g, int x, int y) {
    return x >= 0 && x < g->rows &&
           y >= 0 && y < g->cols;
}

/**
 * Verifica se a célula é caminhável
 */
int gridIsWalkable(Grid *g, int x, int y) {
    if (!gridIsValid(g, x, y))
        return 0;

    return g->cells[x][y] != CELL_OBSTACLE;
}

/**
 * Define o valor de uma célula
 */
void gridSetCell(Grid *g, int x, int y, int value) {
    if (gridIsValid(g, x, y)) {
        g->cells[x][y] = value;
    }
}

/**
 * Obtém o valor de uma célula
 */
int gridGetCell(Grid *g, int x, int y) {
    if (gridIsValid(g, x, y))
        return g->cells[x][y];
    return CELL_OBSTACLE;
}

/**
 * Imprime a grid no terminal
 */
void gridPrint(Grid *g) {
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            switch (g->cells[i][j]) {
                case CELL_EMPTY:    printf(". "); break;
                case CELL_OBSTACLE: printf("# "); break;
                case CELL_PACKAGE:  printf("P "); break;
                case CELL_ROBOT:    printf("R "); break;
            }
        }
        printf("\n");
    }
}

/**
 * Limpa a grid
 */
void gridClear(Grid *g) {
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            g->cells[i][j] = CELL_EMPTY;
        }
    }
}

