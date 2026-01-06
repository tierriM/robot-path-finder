#ifndef MAP_H
#define MAP_H

#include "grid.h"
#include "structures.h"

/*
 * Gera um mapa aleatório válido
 * - obstacle_density: valor entre 0.0 e 1.0
 * - num_packages: número de packages a colocar
 * - start: posição inicial do robot (output)
 * - packages: array onde são colocadas as packages (output)
 */
void map_generate_random(
    Grid *g,
    int max_obstacles,
    int num_packages,
    Point *start,
    Point *packages
);


#endif
