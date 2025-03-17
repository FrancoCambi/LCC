#include "matriz.h"

/*
** Implmentacion utilizando un unico arreglo unidimensional
*/

struct Matriz_ {

  size_t filas;
  size_t columnas;
  double *arr;
};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {

  Matriz *matriz = malloc(sizeof(Matriz));

  matriz->filas = numFilas;
  matriz->columnas = numColumnas;

  matriz->arr = malloc(sizeof(int) * (numFilas * numColumnas));

  if (!matriz->arr) {
    free(matriz);
    return NULL;
  }

  return matriz;

}

void matriz_destruir(Matriz* matriz) {

  if (matriz) {
    free(matriz->arr);
    free(matriz);
  }

}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {

  return matriz->arr[fil * matriz->columnas + col];

}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {

  matriz->arr[fil * matriz->columnas + col] = val;
}

size_t matriz_num_filas(Matriz* matriz) {

  return matriz->filas;
}

size_t matriz_num_columnas(Matriz* matriz) {

  return matriz->columnas;
}
