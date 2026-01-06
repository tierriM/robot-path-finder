#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "pathfinder.h"

static int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

void map_generate_random(
    Grid *g,
    int max_obstacles,
    int num_packages,
    Point *start,
    Point *packages
) {
    int rows = g->rows;
    int cols = g->cols;

    srand(time(NULL));

    while (1) {
        grid_clear(g);

        /* 1️⃣ Robot começa sempre em (0,0) */
        start->x = 0;
        start->y = 0;
        grid_set_cell(g, 0, 0, CELL_ROBOT);

        /* 2️⃣ Packages */
        for (int i = 0; i < num_packages; i++) {
            int x, y;
            do {
                x = random_int(0, rows - 1);
                y = random_int(0, cols - 1);
            } while (grid_get_cell(g, x, y) != CELL_EMPTY);

            packages[i].x = x;
            packages[i].y = y;
            grid_set_cell(g, x, y, CELL_PACKAGE);
        }

        /* 3️⃣ Obstáculos (com limite máximo) */
        int placed = 0;
        while (placed < max_obstacles) {
            int x = random_int(0, rows - 1);
            int y = random_int(0, cols - 1);

            if (grid_get_cell(g, x, y) == CELL_EMPTY) {
                grid_set_cell(g, x, y, CELL_OBSTACLE);
                placed++;
            }
        }

        /* 4️⃣ Verificar se todas as packages são alcançáveis */
        int valid = 1;
        for (int i = 0; i < num_packages; i++) {
            Point tmp_path[1024];
            int len = dijkstra_path(g, *start, packages[i], tmp_path, 1024);
            if (len == 0) {
                valid = 0;
                break;
            }
        }

        if (valid)
            return;
    }
}
