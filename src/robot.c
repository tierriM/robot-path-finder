#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "robot.h"
#include "pathfinder.h"
#include "utils.h"

/**
 * Adiciona um ponto ao caminho completo
 */
static void robotAppendPath(Robot *r, Point *path, int length) {
    for (int i = 0; i < length; i++) {
        if (r->fullPathLength < r->fullPathCapacity) {
            r->fullPath[r->fullPathLength++] = path[i];
        }
    }
}

/**
 * Inicializa o robô
 */
Robot* robotCreate(Point start, Point *packages, int numPackages) {
    Robot *r = malloc(sizeof(Robot));

    r->position = start;
    r->startPosition = start;


    r->packages = packages;
    r->numPackages = numPackages;
    r->visited = calloc(numPackages, sizeof(int));

    r->fullPathCapacity = 1000;
    r->fullPathLength = 0;
    r->fullPath = malloc(sizeof(Point) * r->fullPathCapacity);

    return r;
}

/**
 * Liberta a memória do robô
 */
void robotFree(Robot *r) {
    if (!r) return;
    free(r->visited);
    free(r->fullPath);
    free(r);
}

/**
 * Planeamento completo:
 * - escolhe ordem das packages (vizinho mais próximo)
 * - calcula caminhos com Dijkstra (com pais)
 * - guarda o caminho completo
 */
void robotPlanRoute(Robot *r, Grid *g) {
    int remaining = r->numPackages;
    Point current = r->position;

    while (remaining > 0) {
    int best = -1;
    int bestDist = INT_MAX;
    Point bestPath[1024];
    int bestPathLen = 0;


    for (int i = 0; i < r->numPackages; i++) {
        if (r->visited[i]) continue;

        Point tempPath[1024];
        int len = dijkstraPath(
            g,
            current,
            r->packages[i],
            tempPath,
            1024
        );

        if (len > 0 && len < bestDist) {
            bestDist = len;
            best = i;
            bestPathLen = len;

            for (int k = 0; k < len; k++)
                bestPath[k] = tempPath[k];
        }
    }

    if (best == -1) {
        printf("Erro: nenhuma package alcançável.\n");
        return;
    }

    /* Guardar caminho (ignorar ponto inicial para não duplicar) */
    robotAppendPath(r, bestPath + 1, bestPathLen - 1);

    current = r->packages[best];
    r->visited[best] = 1;
    remaining--;
    }


    /* Voltar à posição inicial */
    Point returnPath[1024];
    int returnLen = dijkstraPath(
        g,
        current,
        r->startPosition,
        returnPath,
        1024
    );

    robotAppendPath(r, returnPath + 1, returnLen - 1);
}

/**
 * Executa o movimento do robô
 */
void robotExecute(Robot *r, Grid *g) {
    printf("Execução do robot:\n");
    
    clearScreen();
    gridPrint(g);
    delayMs(3000);
    printf("\n");

    for (int i = 0; i < r->fullPathLength; i++) {
        Point next = r->fullPath[i];

        gridSetCell(g, r->position.x, r->position.y, CELL_EMPTY);
        r->position = next;
        gridSetCell(g, r->position.x, r->position.y, CELL_ROBOT);

        clearScreen();
        gridPrint(g);
        printf("\n");


        delayMs(500);
    }

    printf("Missão concluída. Robot voltou à base.\n");
}

