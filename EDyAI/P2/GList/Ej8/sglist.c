#include "sglist.h"
#include<stdlib.h>
#include<stdio.h>
#include <assert.h>

SGList sglist_crear() { return NULL; }

void sglist_destruir(SGList lista, FuncionDestructora destruir) {

    GNode *nodeADestruir;

    while (lista != NULL) {
        nodeADestruir = lista;
        lista = lista->next;
        destruir(nodeADestruir->data);
        free(nodeADestruir);
    }
}

SGList sglist_agregar_inicio(SGList lista, void *data, FuncionCopia copiar) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = lista;
  newNode->data = copiar(data);
  return newNode;
}

int sglist_vacia(SGList lista) { return lista == NULL; }

void sglist_recorrer(SGList lista, FuncionVisitante func) {
    for (GNode *node = lista; node != NULL; node = node->next)
        func(node->data);
}

SGList sglist_insertar(SGList lista, void *data, FuncionCopia copiar, FuncionComparadora comparar) {

  if (sglist_vacia(lista) || comparar(lista->data, data) >= 0) 
      return sglist_agregar_inicio(lista, data, copiar);
    
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->data = copiar(data);

  GNode *node;
  for (node = lista; node->next != NULL && comparar(node->next->data, data) < 0; node = node->next);

  newNode->next = node->next;
  node->next = newNode;

  return lista;
}

int sglist_buscar(SGList lista, void *data, FuncionComparadora comparar) {

    for (GNode *node = lista; node != NULL; node = node->next) {
        if (!comparar(data, node->data))
            return 1;
        if (comparar(data, node->data) < 0)
            return 0;
    }

    return 0;

}

SGList sglist_arr(void **arr, int longitud, FuncionCopia copiar, FuncionComparadora comparar) {

    SGList lista = sglist_crear();

    for (int i = 0; i < longitud; i++) 
        lista = sglist_insertar(lista, arr[i], copiar, comparar);
    

    return lista;

}