#include "slist.h"
#include <stdlib.h>

SList* slist_crear() {
  SList* lista = malloc(sizeof(SList));

  lista->primero = NULL;
  lista->ultimo = NULL;

  return lista;
}

SList* slist_agregar_inicio(SList* lista, int dato) {

  SNodo *nodo = malloc(sizeof(SNodo));
  nodo->dato = dato;
  nodo->sig = lista->primero;
  if (lista->ultimo == NULL) {
    lista->ultimo = nodo;
  }
  lista->primero = nodo;

  return lista;
}

SList* slist_agregar_final(SList*lista, int dato) {

  SNodo *nodo = malloc(sizeof(SNodo));
  nodo->dato = dato;
  nodo->sig = NULL;

  if (lista->ultimo != NULL) {
    lista->ultimo->sig = nodo;
  }
  if (lista->primero == NULL) {
    lista->primero = nodo;
  }

  lista->ultimo = nodo;
  
  return lista;
}