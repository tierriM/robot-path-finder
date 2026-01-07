#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "grid.h"
#include "structures.h"

/**
 * Função para calcular caminho mínimo entre start e end.
 * path é um array onde o caminho será guardado (do start até end)
 * maxPathLength é o tamanho máximo de path para evitar overflow.
 * Retorna o número de passos no caminho (0 se não existir)
 */
int dijkstraPath(Grid *g, Point start, Point end, Point *path, int maxPathLength);

#endif
