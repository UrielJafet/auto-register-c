#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "autos.h"
#include "utils.h"



int main() {
    int op, mod;
    char filename[MAX_CHAR];

    SetConsoleOutputCP(CP_UTF8); // Habilita acentos

    do {
        clear();               // Limpia pantalla
        op = menu();           // Muestra menú y retorna opción
        getchar();             // Captura ENTER residual

        switch (op) {
            case 1: {
                printf("\nIngrese un nombre base para los archivos (sin extensión): ");
                leerLinea(filename, MAX_CHAR);
                arch_bin_csv(filename);
                break;
            }
            case 2: {
                printf("\nIngrese el nombre base del archivo (sin extensión): ");
                leerLinea(filename, MAX_CHAR);
                if (check_files(filename)) {
                    printf("Archivos encontrados y listos para usar.\n");
                } else {
                    printf("No se pudieron encontrar los archivos especificados.\n");
                }
                pausar();
                break;
            }
            case 3: {
                clear();
                agregar_carro();
                cargar(filename);
                save_info(filename);
                break;
            }
            case 4: {
                clear();
                mostrar_registro(filename);
                break;
            }
            case 5: {
                clear();
                mod = modificar_registro(filename);
                if (mod != 0) {
                    save_info(filename);
                }
                break;
            }
            case 6: {
                clear();
                printf("\nIngrese el archivo a eliminar (sin extensión): ");
                leerLinea(filename, MAX_CHAR);
                if (!check_files(filename)) {
                    printf("No se pudieron encontrar los archivos especificados.\n");
                    pausar();
                } else {
                    eliminar_archivo_completo(filename);
                }
                break;
            }
            case 7: {
                clear();
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;
            }
            default:
                printf("\nOpción inválida");
                pausar();
                break;
        }

    } while (op != 7);

    return 0;
}