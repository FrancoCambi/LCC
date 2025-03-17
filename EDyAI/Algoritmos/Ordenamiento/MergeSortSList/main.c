#include <stdio.h>
#include <stdlib.h>
#include "slist2.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main(int argc, char *argv[]) {

  SList lista1 = slist_crear();

  lista1 = slist_agregar_final(lista1, 1);
  lista1 = slist_agregar_final(lista1, 3);
  lista1 = slist_agregar_final(lista1, 2);
  lista1 = slist_agregar_final(lista1, 8);
  lista1 = slist_agregar_final(lista1, 5);
  lista1 = slist_agregar_final(lista1, 6);
  lista1 = slist_agregar_final(lista1, 0);
  lista1 = slist_agregar_final(lista1, 55);
  lista1 = slist_agregar_final(lista1, -2);
  lista1 = slist_agregar_final(lista1, -50);
  lista1 = slist_agregar_final(lista1, -4);
  lista1 = slist_agregar_final(lista1, 25);


 /*SList lista2 = slist_crear();

  lista2 = slist_agregar_final(lista2, 2);
  lista2 = slist_agregar_final(lista2, 4);
  lista2 = slist_agregar_final(lista2, 6);

  SList listaMezclada = slist_mezclar(lista1, lista2);*/

  SList listaOrdenada = slist_merge_sort(lista1, 12);

  slist_recorrer(listaOrdenada, imprimir_entero);

  slist_destruir(listaOrdenada);
  slist_destruir(lista1);

  return 0;
}
