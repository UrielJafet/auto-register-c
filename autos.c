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

void arch_bin_csv(const char* filename) {
    //variables para los nombres
    char bin_filename[MAX_CHAR];
    char csv_filename[MAX_CHAR];
    
    //concatenamos cadenas para los archivos
    snprintf(bin_filename, MAX_CHAR, "%s.bin", filename);//imprime los datos formateados
    snprintf(csv_filename, MAX_CHAR, "%s.csv", filename);

    //abrimos archivos .bin y .csv
    FILE* bin_fp = fopen(bin_filename, "wb");
    if (bin_fp == NULL) {
        perror("Error al crear el archivo binario");
        exit(1);
    }
    fclose(bin_fp);

    FILE* csv_fp = fopen(csv_filename, "w");
    if (csv_fp == NULL) {
        perror("Error al crear el archivo CSV");
        exit(1);
    }
    //imprime en el csv el encabezado
    fprintf(csv_fp, "Marca,SubMarca,Modelo,Placa,Color,Numero de serie,Fecha de Entrada,Fecha de Salida\n");
    fclose(csv_fp);

    printf("Archivos '%s' y '%s' creados exitosamente.\n", bin_filename, csv_filename);
    getchar();
}

int check_files(const char* filename) {
    //nombres del archivo
    char bin_filename[MAX_CHAR];
    char csv_filename[MAX_CHAR];
    //les agrega el .bin y .csv
    snprintf(bin_filename, MAX_CHAR, "%s.bin", filename);
    snprintf(csv_filename, MAX_CHAR, "%s.csv", filename);
    //abre archivos en lectura
    FILE* bin_fp = fopen(bin_filename, "rb");
    FILE* csv_fp = fopen(csv_filename, "r");

    if (bin_fp == NULL || csv_fp == NULL) {
        if (bin_fp) fclose(bin_fp);
        if (csv_fp) fclose(csv_fp);
        return 0; // Archivos no encontrados
    }

    fclose(bin_fp);
    fclose(csv_fp);
    return 1; // Archivos encontrados
}

void cargar(const char* filename) {
    //se llama al archivo
    char bin_filename[MAX_CHAR];
    snprintf(bin_filename, MAX_CHAR, "%s.bin", filename);
    //abre el archivo para agregar
    FILE* fp = fopen(bin_filename, "ab");
    if (fp == NULL) {
        perror("Error al abrir el archivo binario...\n");
        exit(1);
    }
    //escribe la informacion en el archivo
    fwrite(&auto_registro[num_registros - 1], sizeof(Carro), 1, fp);
    fclose(fp);
    printf("\nDatos guardados en el archivo binario %s.\n", bin_filename);
}

void save_info(const char* filename) {
    //se llama a los archivos
    char bin_filename[MAX_CHAR];
    snprintf(bin_filename, MAX_CHAR, "%s.bin", filename);
    char csv_filename[MAX_CHAR];
    snprintf(csv_filename, MAX_CHAR, "%s.csv", filename);
    //se abren los archivos
    FILE* bin_file = fopen(bin_filename, "r+b");
    if (bin_file == NULL) {
        perror("Error al abrir el archivo binario.");
        exit(1);
    }
    FILE* csv_file = fopen(csv_filename, "w+");
    if (csv_file == NULL) {
        perror("Error al abrir el archivo csv.");
        exit(1);
    }
    //llamamos a la estructura
    Carro carro;
    //si el encabezado no esta puesto se imprime
    if (csv_file != NULL){
        fprintf(csv_file, "Marca, SubMarca, Modelo, Placa, Color, Numero de serie, Fecha de Entrada, Fecha de Salida\n");
    }
    //hasta que termine de leer el archivo .bin termina e imprime en el .csv la informacion
    while(fread(&carro, sizeof(Carro),1, bin_file)){
        fprintf(csv_file, "%s, %s, %d, %s, %s, %s, %s, %s\n", carro.marca, carro.submarca,
        carro.modelo, carro.placas, carro.color,
        carro.num_serie, carro.fecha_in, carro.fecha_out);
    }

    printf("Vehículo agregado exitosamente\n");
    getchar();

    fclose(bin_file);
    fclose(csv_file);
}

int modificar_registro(const char* filename) {  //función para modificar el registro del carro
    char bin_filename[MAX_CHAR];
    snprintf(bin_filename, MAX_CHAR, "%s.bin", filename);

    FILE *fp = fopen(bin_filename, "r+b");  //abriremos el archivo binario en modo lectura y escritura
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        exit(1);
    }

    char plac[MAX_CHAR];
    printf("\nIngrese la placa del Vehículo a modificar: ");
    fgets(plac, MAX_CHAR, stdin);  //almacenará la placa del vehiculo a modifidicar
    strtok(plac, "\n");  //Elimina el salto de línea

    Carro carro;
    int existe = 0;
    int opc;

    while (fread(&carro, sizeof(Carro), 1, fp) == 1) {  //lee los registros del Carro y los almacena en la variable carro
        if (strcmp(plac, carro.placas) == 0) {  
            //la función strcmp comparará las dos cadenas de caracteres hasta encontrar el registro que coincida con la placa ingresada
            printf("Marca: %s\n", carro.marca);
            printf("SubMarca: %s\n", carro.submarca);
            printf("Modelo: %d\n", carro.modelo);
            printf("Placas: %s\n", carro.placas);
            printf("Color: %s\n", carro.color);
            printf("Número de serie: %s\n", carro.num_serie);
            printf("Fecha de Entrada: %s\n", carro.fecha_in);
            printf("Fecha de Salida: %s\n", carro.fecha_out);
            printf("\n1.-Color \n2.-Fecha de entrada \n3.-Fecha de Salida ");
            printf("\n¿Qué datos desea modificar? ");
            scanf("%d", &opc);
            getchar();

            if (opc == 1){  //si el usuario elige la opcion 1, se le pediráque ingrese el nuevo color del vehiculo y así con demás opciones
                printf("Color: ");
                fgets(carro.color, MAX_CHAR, stdin);
                strtok(carro.color, "\n");
            } else if (opc == 2){
                printf("Fecha de Entrada (DD/MM/AAAA): ");
                fgets(carro.fecha_in, MAX_CHAR, stdin);
                strtok(carro.fecha_in, "\n");
            }else if (opc == 3){
                printf("Fecha de Salida (DD/MM/AAAA): ");
                fgets(carro.fecha_out, MAX_CHAR, stdin);
                strtok(carro.fecha_out, "\n");
            }

            long pos = ftell(fp) - sizeof(Carro);  //Calcula la posición en el archivo donde comienza el último el ultimo objeto  "Carro" leído
            fseek(fp, pos, SEEK_SET);  //función que mueve el puntero de posición del archivo a la posición especififcada
            fwrite(&carro, sizeof(Carro), 1, fp);
            printf("Se modificó exitosamente\n");
            existe = 1;
            break;
        }
    }

    if (!existe) {
        printf("No existe la placa ingresada\n");
        getchar();
    }

    return existe;
    fclose(fp);
    getchar();
}

void mostrar_registro(const char* filename) {
    //se guarda el nombre del archivo
    char bin_filename[MAX_CHAR];
    snprintf(bin_filename, MAX_CHAR, "%s.bin", filename);
    //se abre
    FILE* fp = fopen(bin_filename, "rb");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        exit(1);
    }
    //llamado a la estructura
    Carro carro;

    printf("\n<------------ Registros de Vehículos ------------>\n");
    //lee el archivo .bin y muestra la
    while (fread(&carro, sizeof(Carro), 1, fp) == 1) {
        printf("\tMarca: %s\n", carro.marca);
        printf("\tSubMarca: %s\n", carro.submarca);
        printf("\tModelo: %d\n", carro.modelo);
        printf("\tPlacas: %s\n", carro.placas);
        printf("\tColor: %s\n", carro.color);
        printf("\tNúmero de serie: %s\n", carro.num_serie);
        printf("\tFecha de Entrada: %s\n", carro.fecha_in);
        printf("\tFecha de Salida: %s\n", carro.fecha_out);
        printf("-----------------------------------------------------\n");
    }

    fclose(fp);
    getchar();
}

void eliminar_archivo_completo(const char* filename) { // funcion para eliminar archivo
    char bin_filename[MAX_CHAR]; 
    char csv_filename[MAX_CHAR];

    snprintf(bin_filename, MAX_CHAR, "%s.bin", filename);// concatenar en binario
    snprintf(csv_filename, MAX_CHAR, "%s.csv", filename); // concatenar en csv
    if (remove(bin_filename) == 0 && remove(csv_filename) == 0) { // si se elimino el bin y csv
        printf("Archivos '%s' y '%s' eliminados exitosamente.\n", bin_filename, csv_filename); 
    } else {
        perror("Error al eliminar los archivos"); //error al eliminar archivo
    }
    getchar();
}

