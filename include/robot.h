#ifndef ROBOT_H
#define ROBOT_H

#include "grid.h"
#include "structures.h"

typedef struct {
    Point position;
    Point startPosition;

    Point *packages;
    int numPackages;
    int *visited;

    Point *fullPath;
    int fullPathLength;
    int fullPathCapacity;
} Robot;

/**
 * Inicialização
 */
Robot* robotCreate(Point start, Point *packages, int numPackages);
/**
 * Liberta a memória do robô
 */
void robotFree(Robot *r);

/**
 * Planeamento
 */
void robotPlanRoute(Robot *r, Grid *g);

/**
 * Execução
 */
void robotExecute(Robot *r, Grid *g);

#endif
