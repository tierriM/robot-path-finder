#include "utils.h"

#ifdef _WIN32
    #include <windows.h>
    #include <stdlib.h>
#else
    #include <unistd.h>
    #include <stdlib.h>
#endif

/**
 * Delay em milissegundos
 */
void delayMs(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

/**
 * Limpa o ecrã do terminal
 */
void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
