#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Casos de prueba para arboles de busqueda binaria generales
 */

#define N_PALABRAS 10

static void *copiar_cadena(void *dato) {
  char *str = malloc(sizeof(char) * (strlen(dato) + 1));
  assert(str != NULL);
  strcpy(str, dato);
  return str;
}

static void *copiar_entero(void *dato) {
  int* num = malloc(sizeof(int));
  *num = *(int*)dato;
  return num;
}
static int comparar_cadena(void *dato1, void *dato2) {
  return strcmp(dato1, dato2);
}
static int comparar_puntero_entero(void* i1, void* i2) {
  return (*(int*)i1 - *(int*)i2);
}

void destruir_cadena(void *dato) { free(dato); }
void destruir_entero(void* dato) {free(dato); }
static void imprimir_cadena(void *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("\"%s\" ", (char *)dato);
}

static void imprimir_entero(void *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("\"%d\" ", *(int *)dato);
}
int main() {

  char *palabras[N_PALABRAS] = {"gatos",      "perro",    "casa",     "persona",
                                "parque",    "arbol",    "edificio", "calle",
                                "argentina", "santa fe"};

  // Creamos un arbol vacio y le insertamos las palabras
  BSTree arbol = bstee_crear();
  for (int i = 0; i < N_PALABRAS; i++) 
    arbol = bstree_insertar(arbol, palabras[i], copiar_cadena, comparar_cadena);
  

  // Imprimir el arbol inorden (alfabetico)
  printf("Recorrido inorden : ");
  //bstree_recorrer_intervalo(arbol, "perro", "santa fe", imprimir_cadena, NULL, comparar_cadena);
  puts("\n");


  void **arr = malloc(sizeof(void*) * 7);

  int a = 2;
  int b = 7;
  int c = 9;
  int d = 6;
  int e = 10;

  arr[0] = &a;
  arr[1] = &b;
  arr[2] = &c;
  arr[3] = &d;
  arr[4] = NULL;
  arr[5] = NULL;
  arr[6] = &e;

  BSTree arbolCreado = bstree_bfs_to_tree(arr, 7, copiar_entero, comparar_puntero_entero);

  printf("%d\n", bstree_validar(arbolCreado, comparar_puntero_entero));
  bstree_recorrer(arbolCreado, BTREE_RECORRIDO_PRE, imprimir_entero, NULL);

  bstree_destruir(arbolCreado, destruir_entero);
  free(arr);

  //printf("%d", bstree_validar(arbol, comparar_cadena));

  //arbol = bstree_eliminar(arbol, "calle", comparar_cadena, destruir_cadena, copiar_cadena);


  // Buscar elementos
  /*assert(bstree_buscar(arbol, "farmacia", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "santa fe", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "persona", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "unr", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "argentina", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "telefono", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "mail", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "parques", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "EDyA1", comparar_cadena) == 0);*/



  // Destruir arbol
  bstree_destruir(arbol, destruir_cadena);

  return 0;
}
