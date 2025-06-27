#ifndef AUTOS_H
#define AUTOS_H

#define MAX_REGISTROS 50
#define MAX_CHAR 50

typedef struct {
    char marca[MAX_CHAR];
    char submarca[MAX_CHAR];
    int modelo;
    char placas[MAX_CHAR];
    char color[MAX_CHAR];
    char num_serie[MAX_CHAR];
    char fecha_in[MAX_CHAR];
    char fecha_out[MAX_CHAR];
} Carro;

int menu();
void agregar_carro();
void arch_bin_csv(const char* filename);
int check_files(const char* filename);
void cargar(const char* filename);
void save_info(const char* filename);
void mostrar_registro(const char* filename);
void eliminar_archivo_completo(const char* filename);
int modificar_registro(const char* filename);


#endif // AUTOS_H