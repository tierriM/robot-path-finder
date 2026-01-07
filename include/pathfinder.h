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

/**
 * Calcula as distâncias mínimas desde start até todos os packages ainda não visitados.
 * distances: array onde serão guardadas as distâncias
 * packages: array de posições dos packages
 * numPackages: número de packages
 * visited: array que indica se o package já foi visitado
 * Retorna o número de packages encontrados
 */
int dijkstraFindPackages(
    Grid *g,
    Point start,
    Point *packages,
    int numPackages,
    int *visited,
    int *distances
);

#endif
