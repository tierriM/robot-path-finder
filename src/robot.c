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
        int *distances = malloc(sizeof(int) * r->num_packages);
        for (int i = 0; i < r->num_packages; i++)
            distances[i] = INT_MAX;

        /* Descobrir distâncias até todas as packages não visitadas */
        int found = dijkstra_find_packages(
            g,
            current,
            r->packages,
            r->num_packages,
            r->visited,
            distances
        );

        if (found == 0) {
            printf("Erro: não foi possível encontrar mais packages.\n");
            free(distances);
            return;
        }

        /* Escolher a package mais próxima */
        int best = -1;
        int best_dist = INT_MAX;

        for (int i = 0; i < r->num_packages; i++) {
            if (!r->visited[i] && distances[i] < best_dist) {
                best_dist = distances[i];
                best = i;
            }
        }

        if (best == -1) {
            free(distances);
            break;
        }

        /* Calcular caminho exacto até essa package */
        Point temp_path[1024];
        int path_len = dijkstra_path(
            g,
            current,
            r->packages[best],
            temp_path,
            1024
        );

        /* Guardar caminho (ignorar o primeiro ponto para evitar duplicações) */
        robot_append_path(r, temp_path + 1, path_len - 1);

        /* Atualizar estado */
        current = r->packages[best];
        r->visited[best] = 1;
        remaining--;

        free(distances);
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

        delay_ms(300);
    }

    printf("Missão concluída. Robot voltou à base.\n");
}

