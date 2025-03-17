#include "contacto2.h"
#include "glist2.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  GList lista = glist_crear();
  Contacto *contactos[6];
  contactos[0] = contacto_crear("g", "3412695452", 20);
  contactos[1] = contacto_crear("e", "3412684759", 25);
  contactos[2] = contacto_crear("d", "3415694286", 30);
  contactos[3] = contacto_crear("c", "3416259862", 31);
  contactos[4] = contacto_crear("b", "3416874594", 33);
  contactos[5] = contacto_crear("b", "3416894526", 64);

  for (int i = 0; i < 6; ++i) {
    lista =
        glist_agregar_inicio(lista, contactos[i], (FuncionCopia)contacto_copia);
    contacto_destruir(contactos[i]);
  }

  printf("Lista:\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);

  printf("\n\nLista insertada:\n");

  Contacto *cont = contacto_crear("a", "3415886950", 55);
  lista = glist_insertar(lista, cont, (FuncionCopia)contacto_copia, (FuncionComparadora)contacto_comparar);

  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);

  glist_destruir(lista, (FuncionDestructora)contacto_destruir);

  return 0;
}