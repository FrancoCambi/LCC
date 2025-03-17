#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main(int argc, char *argv[]) {

  SList* lista = slist_crear();

  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_final(lista, 3);

  printf("%d", lista->ultimo->dato);

  return 0;
}
