#ifndef ROBOT_H
#define ROBOT_H

#include "grid.h"
#include "structures.h"

typedef struct {
    Point position;
    Point start_position;

    Point *packages;
    int num_packages;
    int *visited;

    Point *full_path;
    int full_path_length;
    int full_path_capacity;
} Robot;

/* Inicialização */
Robot* robot_create(Point start, Point *packages, int num_packages);
void robot_free(Robot *r);

/* Planeamento */
void robot_plan_route(Robot *r, Grid *g);

/* Execução */
void robot_execute(Robot *r, Grid *g);

#endif
