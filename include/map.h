#ifndef MAP_H
#define MAP_H

#include "grid.h"
#include "structures.h"

/**
 * Gera um mapa aleatório válido
 * - maxObstacles: número máximo de obstáculos
 * - numPackages: número de packages a colocar
 * - start: posição inicial do robot (output)
 * - packages: array onde são colocadas as packages (output)
 */
void mapGenerateRandom(
    Grid *g,
    int maxObstacles,
    int numPackages,
    Point *start,
    Point *packages
);


#endif
