#include "autos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

Carro auto_registro[MAX_REGISTROS];
int num_registros = 0;

int menu() {
    int opcion;
    printf("<------------Menu------------>");
    printf("\n1. Crear Archivo Nuevo");
    printf("\n2. Usar archivo viejo");
    printf("\n3. Agregar registro del carro");
    printf("\n4. Mostrar registros del carro");
    printf("\n5. Modificar registro del carro");
    printf("\n6. Eliminar archivo del carro");
    printf("\n7. Salir");
    printf("\nIngrese opción:");
    scanf("%d", &opcion);

    return opcion;
}

void agregar_carro() {
    clear();
    //revisa que pueda ingresar registros
    if (num_registros >= MAX_REGISTROS) {
        printf("\nMáximo de registros alcanzado");
        return;
    }

    printf("<------------Ingrese información del Vehículo------------>\n");

    printf("Marca: ");
    fgets(auto_registro[num_registros].marca, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].marca, "\n");

    printf("SubMarca: ");
    fgets(auto_registro[num_registros].submarca, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].submarca, "\n");

    printf("Modelo: ");
    char modelo_str[MAX_CHAR];
    fgets(modelo_str, MAX_CHAR, stdin);
    sscanf(modelo_str, "%d", &auto_registro[num_registros].modelo); // Para que se guarde en entero :)

    printf("Placas: ");
    fgets(auto_registro[num_registros].placas, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].placas, "\n");

    printf("Color: ");
    fgets(auto_registro[num_registros].color, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].color, "\n");

    printf("Número de serie: ");
    fgets(auto_registro[num_registros].num_serie, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].num_serie, "\n");

    printf("Fecha de Entrada (DD/MM/AAAA): ");
    fgets(auto_registro[num_registros].fecha_in, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].fecha_in, "\n");

    printf("Fecha de Salida (DD/MM/AAAA): ");
    fgets(auto_registro[num_registros].fecha_out, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].fecha_out, "\n");

    num_registros++;//aumenta en uno los autos registrados
}