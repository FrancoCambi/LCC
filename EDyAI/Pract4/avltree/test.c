#include "avl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Casos de prueba para arboles AVL
 */

 /**
  * Funciones para usar arboles AVL con datos de tipo int *
  */
static void* copiar_puntero_entero(void* i) {
  int* p = malloc(sizeof(int));
  *p = *(int*)i;
  return p;
}
static int comparar_puntero_entero(void* i1, void* i2) {
  return (*(int*)i1 - *(int*)i2);
}
static void destruir_puntero_entero(void* i) { free(i); }
static void imprimir_puntero_entero(void* i,
  __attribute__((unused)) void* extra) {
  printf("%d ", *(int*)i);
}

int main() {

  // caso de prueba 1:
  // se insertan 500 enteros aleatorios entre 0 y 999,
  // validando que cada arbol intermedio sea AVL
  AVL arbol = avl_crear(copiar_puntero_entero, comparar_puntero_entero,
    destruir_puntero_entero);
  for (int i = 0; i < 1000; ++i) {
    int e = i;
    avl_insertar(arbol, &e);
    assert(avl_validar(arbol) == 1);
  }
  printf("Insert tests -> OK\n");

  for (int i = 0; i < 20000; ++i) {
    int i = rand() % 1000;
    arbol = avl_eliminar(arbol, &i);
    assert(avl_validar(arbol) == 1);
  }
  printf("ELiminar tests -> OK\n");

  // caso de prueba 2:
  // arbol AVL de la practica,
  // imprimiendo en preorden cada arbol intermedio
  AVL arbol2 = avl_crear(copiar_puntero_entero, comparar_puntero_entero,
    destruir_puntero_entero);
  int numeros[] = { 10, 20, 15, 25, 30, 16, 18, 19 , 40, 50, 60, 70, 45};
  for (int i = 0; i < 13; ++i) {
    avl_insertar(arbol2, numeros + i);
    printf("Se inserto %d. Recorrido PREORDER: " , numeros[i]);
    avl_recorrer(arbol2, AVL_RECORRIDO_PRE, imprimir_puntero_entero, NULL);
    puts("");
  }
  
  int d = 25;
  arbol2 = avl_eliminar(arbol2, &d);
  printf("\nSe elimino %d\n", d);
  printf("%s\n", avl_validar(arbol2) == 1 ? "Arbol AVL valido." : "No valido");
  printf("Recorrido PREORDER: ");
  avl_recorrer(arbol2, AVL_RECORRIDO_PRE, imprimir_puntero_entero, NULL);

  avl_destruir(arbol2);
  avl_destruir(arbol);

  puts("\nTodo ok :D");

  return 0;
}