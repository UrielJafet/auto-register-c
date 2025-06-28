# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Iinclude

# Buscar todos los .c dentro de src/
SRC = $(wildcard src/*.c)

# Nombre del binario de salida (agrega .exe si estás en Windows)
OUT = build/registro_autos.exe

# Regla por defecto: compilar todo
all: $(OUT)

# Cómo compilar
$(OUT): $(SRC)
	if not exist build mkdir build
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

# Ejecutar el programa
run: all
	$(OUT)

# Limpiar archivos binarios
clean:
	if exist build rmdir /s /q build
