#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "robot.h"
#include "structures.h"

int main(void) {
    /* ---------- Criar grid ---------- */
    int rows = 6;
    int cols = 8;

    Grid *grid = grid_create(rows, cols);

    /* ---------- Obstáculos ---------- */
    grid_set_cell(grid, 1, 2, CELL_OBSTACLE);
    grid_set_cell(grid, 2, 2, CELL_OBSTACLE);
    grid_set_cell(grid, 3, 2, CELL_OBSTACLE);
    grid_set_cell(grid, 4, 4, CELL_OBSTACLE);

    /* ---------- Packages ---------- */
    Point packages[] = {
        {0, 6},
        {4, 6},
        {5, 1}
    };
    int num_packages = 3;

    for (int i = 0; i < num_packages; i++) {
        grid_set_cell(grid, packages[i].x, packages[i].y, CELL_PACKAGE);
    }

    /* ---------- Robot ---------- */
    Point start = {0, 0};
    grid_set_cell(grid, start.x, start.y, CELL_ROBOT);

    Robot *robot = robot_create(start, packages, num_packages);

    /* ---------- Estado inicial ---------- */
    printf("Mapa inicial:\n");
    grid_print(grid);
    printf("\n");

    /* ---------- Planeamento ---------- */
    printf("A planear rota...\n\n");
    robot_plan_route(robot, grid);

    /* ---------- Execução ---------- */
    robot_execute(robot, grid);

    /* ---------- Limpeza ---------- */
    robot_free(robot);
    grid_free(grid);

    return 0;
}
