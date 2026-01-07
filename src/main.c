#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "robot.h"
#include "structures.h"
#include "map.h"


int main(void) {
    /* ---------- Criar grid ---------- */
    int rows = 8;
    int cols = 8;

    Grid *grid = gridCreate(rows, cols);

    Point start = {0, 0};
    int numPackages = 3;
    int maxObstacles = 10;
    Point packages[numPackages];

    mapGenerateRandom(
        grid,
        maxObstacles,
        numPackages,
        &start,
        packages
    );

    for (int i = 0; i < numPackages; i++) {
        gridSetCell(grid, packages[i].x, packages[i].y, CELL_PACKAGE);
    }

    /* ---------- Robot ---------- */
    gridSetCell(grid, start.x, start.y, CELL_ROBOT);

    Robot *robot = robotCreate(start, packages, numPackages);

    /* ---------- Estado inicial ---------- */
    printf("Mapa inicial:\n");
    gridPrint(grid);
    printf("\n");

    /* ---------- Planeamento ---------- */
    printf("A planear rota...\n\n");
    robotPlanRoute(robot, grid);

    /* ---------- Execução ---------- */
    robotExecute(robot, grid);

    /* ---------- Limpeza ---------- */
    robotFree(robot);
    gridFree(grid);

    return 0;
}
