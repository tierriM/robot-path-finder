#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "robot.h"
#include "pathfinder.h"
#include "utils.h"

/* Adiciona um ponto ao caminho completo */
static void robot_append_path(Robot *r, Point *path, int length) {
    for (int i = 0; i < length; i++) {
        if (r->full_path_length < r->full_path_capacity) {
            r->full_path[r->full_path_length++] = path[i];
        }
    }
}

Robot* robot_create(Point start, Point *packages, int num_packages) {
    Robot *r = malloc(sizeof(Robot));

    r->position = start;
    r->start_position = start;

    r->packages = packages;
    r->num_packages = num_packages;

    r->visited = calloc(num_packages, sizeof(int));

    r->full_path_capacity = 1000; // suficiente para grids médias
    r->full_path_length = 0;
    r->full_path = malloc(sizeof(Point) * r->full_path_capacity);

    return r;
}

void robot_free(Robot *r) {
    if (!r) return;
    free(r->visited);
    free(r->full_path);
    free(r);
}

/*
 * Planeamento completo:
 * - escolhe ordem das packages (vizinho mais próximo)
 * - calcula caminhos com Dijkstra (com pais)
 * - guarda o caminho completo
 */
void robot_plan_route(Robot *r, Grid *g) {
    int remaining = r->num_packages;
    Point current = r->position;

    while (remaining > 0) {
    int best = -1;
    int best_dist = INT_MAX;
    Point best_path[1024];
    int best_path_len = 0;

    for (int i = 0; i < r->num_packages; i++) {
        if (r->visited[i]) continue;

        Point temp_path[1024];
        int len = dijkstra_path(
            g,
            current,
            r->packages[i],
            temp_path,
            1024
        );

        if (len > 0 && len < best_dist) {
            best_dist = len;
            best = i;
            best_path_len = len;

            for (int k = 0; k < len; k++)
                best_path[k] = temp_path[k];
        }
    }

    if (best == -1) {
        printf("Erro: nenhuma package alcançável.\n");
        return;
    }

    /* Guardar caminho (ignorar ponto inicial para não duplicar) */
    robot_append_path(r, best_path + 1, best_path_len - 1);

    current = r->packages[best];
    r->visited[best] = 1;
    remaining--;
    }


    /* Voltar à posição inicial */
    Point return_path[1024];
    int return_len = dijkstra_path(
        g,
        current,
        r->start_position,
        return_path,
        1024
    );

    robot_append_path(r, return_path + 1, return_len - 1);
}

void robot_execute(Robot *r, Grid *g) {
    printf("Execução do robot:\n");

    for (int i = 0; i < r->full_path_length; i++) {
        Point next = r->full_path[i];

        grid_set_cell(g, r->position.x, r->position.y, CELL_EMPTY);
        r->position = next;
        grid_set_cell(g, r->position.x, r->position.y, CELL_ROBOT);

        clear_screen();
        grid_print(g);
        printf("\n");

        delay_ms(500);
    }

    printf("Missão concluída. Robot voltou à base.\n");
}

