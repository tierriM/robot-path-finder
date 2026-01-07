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

/**
 * Cria uma nova grid
 */
Grid* gridCreate(int rows, int cols);
/**
 * Liberta a memória da grid
 */
void gridFree(Grid *g);

/**
 * Define o valor de uma célula
 */
void gridSetCell(Grid *g, int x, int y, int value);
/**
 * Obtém o valor de uma célula
 */
int  gridGetCell(Grid *g, int x, int y);

/**
 * Verifica se a posição é válida na grid
 */
int  gridIsValid(Grid *g, int x, int y);
/**
 * Verifica se a célula é caminhável
 */
int  gridIsWalkable(Grid *g, int x, int y);

/**
 * Imprime a grid no terminal
 */
void gridPrint(Grid *g);
/**
 * Limpa a grid
 */
void gridClear(Grid *g);


#endif
