#ifndef GRID_H
#define GRID_H

#include "structures.h"

/* Tipos de células */
#define CELL_EMPTY     0
#define CELL_OBSTACLE -1
#define CELL_PACKAGE   1
#define CELL_ROBOT     2

typedef struct {
    int rows;
    int cols;
    int **cells;
} Grid;

/* Funções da grid */
Grid* grid_create(int rows, int cols);
void grid_free(Grid *g);

void grid_set_cell(Grid *g, int x, int y, int value);
int  grid_get_cell(Grid *g, int x, int y);

int  grid_is_valid(Grid *g, int x, int y);
int  grid_is_walkable(Grid *g, int x, int y);

void grid_print(Grid *g);
void grid_clear(Grid *g);


#endif
