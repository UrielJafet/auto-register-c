
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Función para limpiar stdin y eliminar '\n'
void leerLinea(char *destino, int max) {
    fgets(destino, max, stdin);
    strtok(destino, "\n"); // elimina '\n'
}

// Pausar para mostrar mensajes
void pausar() {
    printf("\nPresione ENTER para continuar...");
    getchar();
}

//Limpia pantalla
void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif // Para limpiar la consola en Windows
}