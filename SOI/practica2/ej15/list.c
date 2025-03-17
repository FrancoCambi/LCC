#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar->key);
    free(nodoAEliminar->value);
    free(nodoAEliminar);
  }
}

SList slist_agregar_inicio(SList lista, char * key, char * value) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->key = strdup(key);
  nuevoNodo->value = strdup(value);
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

// Eliminar un par de la lista con la clave indicada
SList slist_borrar_par(SList lista, char *key) {
  SNodo *anterior = NULL;
  SNodo *actual = lista;

  while (actual != NULL) {
    if (strcmp(actual->key, key) == 0) {
      if (anterior == NULL) {
        lista = actual->sig;
      } else {
        anterior->sig = actual->sig;
      }
      free(actual->key);
      free(actual->value);
      free(actual);
      break;
    }
    anterior = actual;
    actual = actual->sig;
  }
  return lista;
}

char * slist_buscar(SList lista, char * key) {
  SNodo *actual = lista;

  while (actual != NULL) {
    if (strcmp(actual->key, key) == 0) {
      return actual->value;
    }
    actual = actual->sig;
  }
  return NULL;
}

void slist_imprimir(SList lista) {
  printf("\n\nLista: ");
  for(;lista; lista=lista->sig)  {
    printf("(%s - %s) ", lista->key, lista->value);
  }
}