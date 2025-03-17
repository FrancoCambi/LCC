#include "matriz.h"

/*
** Implementacion utilizando un arreglo bidimensional (arreglo de punteros a arreglo)
*/

struct Matriz_ {

  size_t filas, columnas;
  double **arr;

};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {

  Matriz *matriz = malloc(sizeof(Matriz));

  matriz->filas = numFilas;
  matriz->columnas = numColumnas;

  matriz->arr = (double**) malloc(sizeof(double*) * numFilas);

  if (!matriz->arr) {
    free(matriz);
    return NULL;
  }

  for (int i = 0; i < numFilas; i++)
    matriz->arr[i] = (double*) malloc(sizeof(double) * numColumnas);

  return matriz;
}

void matriz_destruir(Matriz* matriz) {

  if (matriz) {
    for (int i = 0; i < matriz->filas; i++) 
      free(matriz->arr[i]);
    free(matriz->arr);
    free(matriz);
  }
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {

  return matriz->arr[fil][col];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {

  matriz->arr[fil][col] = val;
}

size_t matriz_num_filas(Matriz* matriz) {

  return matriz->filas;
}

size_t matriz_num_columnas(Matriz* matriz) {

  return matriz->columnas;
}


