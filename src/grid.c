#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

Grid* grid_create(int rows, int cols) {
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

void grid_free(Grid *g) {
    if (!g) return;

    for (int i = 0; i < g->rows; i++) {
        free(g->cells[i]);
    }
    free(g->cells);
    free(g);
}

int grid_is_valid(Grid *g, int x, int y) {
    return x >= 0 && x < g->rows &&
           y >= 0 && y < g->cols;
}

int grid_is_walkable(Grid *g, int x, int y) {
    if (!grid_is_valid(g, x, y))
        return 0;

    return g->cells[x][y] != CELL_OBSTACLE;
}

void grid_set_cell(Grid *g, int x, int y, int value) {
    if (grid_is_valid(g, x, y)) {
        g->cells[x][y] = value;
    }
}

int grid_get_cell(Grid *g, int x, int y) {
    if (grid_is_valid(g, x, y))
        return g->cells[x][y];
    return CELL_OBSTACLE;
}

void grid_print(Grid *g) {
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
