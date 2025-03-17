# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra -g

# Archivos fuente
SOURCES = test.c avl.c

# Archivos de cabecera
HEADERS = $(SOURCES:.c=.h)

# Nombre del ejecutable
EXECUTABLE = a.out

# Objetos generados
OBJECTS = $(SOURCES:.c=.o)

# Regla principal
all: $(EXECUTABLE)

# Regla para compilar los objetos
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para enlazar los objetos y generar el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)