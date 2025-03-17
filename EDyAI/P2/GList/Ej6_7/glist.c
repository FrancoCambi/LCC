#include "glist2.h"
#include "contacto2.h"
#include <assert.h>
#include <stdlib.h>
#include<stdio.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

GList glist_filtrar(GList lista, FuncionCopia c, Predicado p) {

  GList listaFiltrada = glist_crear();

  for (GNode *node = lista; node != NULL; node = node->next) 
    if (p(node->data)) 
      listaFiltrada = glist_agregar_inicio(listaFiltrada, node->data, c);
      
  return listaFiltrada;
}

GList glist_insertar(GList lista, void *data, FuncionCopia copiar, FuncionComparadora comparar) {

  if (glist_vacia(lista) || comparar(lista->data, data) >= 0) 
      return glist_agregar_inicio(lista, data, copiar);
    
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->data = copiar(data);

  GNode *node;
  for (node = lista; node->next != NULL && comparar(node->next->data, data) < 0; node = node->next);

  newNode->next = node->next;
  node->next = newNode;

  return lista;
}