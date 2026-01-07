#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "pathfinder.h"

/**
 * Gera um inteiro aleatório entre min e max
 */
static int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

/**
 * Gera um mapa aleatório válido
 */
void mapGenerateRandom(
    Grid *g,
    int maxObstacles,
    int numPackages,
    Point *start,
    Point *packages
) {
    int rows = g->rows;
    int cols = g->cols;

    srand(time(NULL));

    while (1) {
        gridClear(g);

        /* 1️⃣ Robot começa sempre em (0,0) */
        start->x = 0;
        start->y = 0;
        gridSetCell(g, 0, 0, CELL_ROBOT);

        /* 2️⃣ Packages */
        for (int i = 0; i < numPackages; i++) {
            int x, y;
            do {
                x = randomInt(0, rows - 1);
                y = randomInt(0, cols - 1);
            } while (gridGetCell(g, x, y) != CELL_EMPTY);

            packages[i].x = x;
            packages[i].y = y;
            gridSetCell(g, x, y, CELL_PACKAGE);
        }

        /* 3️⃣ Obstáculos (com limite máximo) */
        int placed = 0;
        while (placed < maxObstacles) {
            int x = randomInt(0, rows - 1);
            int y = randomInt(0, cols - 1);

            if (gridGetCell(g, x, y) == CELL_EMPTY) {
                gridSetCell(g, x, y, CELL_OBSTACLE);
                placed++;
            }
        }

        /* 4️⃣ Verificar se todas as packages são alcançáveis */
        int valid = 1;
        for (int i = 0; i < numPackages; i++) {
            Point tmpPath[1024];
            int len = dijkstraPath(g, *start, packages[i], tmpPath, 1024);
            if (len == 0) {
                valid = 0;
                break;
            }
        }

        if (valid)
            return;
    }
}
