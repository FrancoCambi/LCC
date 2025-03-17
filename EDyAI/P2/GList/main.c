#include "contacto.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  GList lista = glist_crear();
  Contacto *contactos[6];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 1);
  contactos[3] = contacto_crear("Paola Argento", "3416259862", 2);
  contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  for (int i = 0; i < 6; ++i) {
    lista =
        glist_agregar_inicio(lista, contactos[i], (FuncionCopia)contacto_copia);
    contacto_destruir(contactos[i]);
  }

  printf("Lista:\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);

  printf("\n\nLista filtrada:\n");

  GList listaFiltrada = glist_crear();
  listaFiltrada = glist_filtrar(lista, (FuncionCopia)contacto_copia, (Predicado)contacto_mayor);

  glist_recorrer(listaFiltrada, (FuncionVisitante)contacto_imprimir);

  glist_destruir(listaFiltrada, (FuncionDestructora)contacto_destruir);

  glist_destruir(lista, (FuncionDestructora)contacto_destruir);

  return 0;
}