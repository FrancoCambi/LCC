#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main(int argc, char *argv[]) {

  SList lista = slist_crear();

  lista = slist_agregar_final(lista, 1);
  lista = slist_agregar_final(lista, 2);
  lista = slist_agregar_final(lista, 3);
  lista = slist_agregar_final(lista, 4);
  lista = slist_agregar_final(lista, 4);
  lista = slist_agregar_final(lista, 8);
  lista = slist_agregar_final(lista, 9);
  lista = slist_agregar_final(lista, 9);

  SList lista2 = slist_crear();

  lista2 = slist_agregar_final(lista2, 5);
  lista2 = slist_agregar_final(lista2, 6);

  SList listaIntercalada = slist_partir(lista);

  slist_recorrer(listaIntercalada, imprimir_entero);

  return 0;
}
