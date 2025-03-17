#include "slist.h"
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

size_t slist_longitud(SList lista) {

  size_t longitud = 0;

  SList nodo = lista;
  for (; nodo != NULL; nodo = nodo->sig, ++longitud);

  return longitud;
}

SList slist_concatenar(SList lista1, SList lista2) {

  SNodo *listaCopia = lista1;

  for (; lista1->sig != NULL; lista1 = lista1->sig);

  lista1->sig = lista2;

  return listaCopia;

}

SList slist_insertar(SList lista, int dato, size_t pos) {

  if (pos == 0) {
    return slist_agregar_inicio(lista, dato);
  }

  SNodo *listaCopia = lista;
  SNodo *nuevoNodo = malloc(sizeof(SNodo));

  for (int i = 1; i < pos && lista->sig != NULL; i++, lista = lista->sig);
  /* Ahora lista apunta al nodo en la posición pos*/

  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista->sig;

  lista->sig = nuevoNodo;
  
  return listaCopia;

}

SList slist_eliminar(SList lista, size_t pos) {

  SNodo *listaCopia;

  if (pos == 0) {
    listaCopia = lista->sig;
    free(lista);
  }
  
  else {

    listaCopia = lista;

    for (int i = 1; i < pos && lista->sig != NULL; i++, lista = lista->sig);

    SNodo *direccionLiberar = lista->sig;
    lista->sig = lista->sig->sig;
    free(direccionLiberar);

  }

    return listaCopia;
}

int slist_contiene(SList lista, int dato) {

  int encontrado = 0;

  while (lista != NULL && !encontrado) {
    if (lista->dato == dato)
      encontrado = 1;

    lista = lista->sig;
  }

  return encontrado;
}

size_t slist_indice(SList lista, int dato) {

  size_t contador = 0;

  while (lista != NULL) {
    if (lista->dato == dato)
      return contador;

    lista = lista->sig;
    contador++;
  }

  return -1;
}

SList slist_intersecar(SList lista1, SList lista2) {

  SList nuevaLista = slist_crear();

  while (lista1 != NULL) {

    if (slist_contiene(lista2, lista1->dato)) {
      nuevaLista = slist_agregar_final(nuevaLista, lista1->dato);

    }
    lista1 = lista1->sig;
  }

  return nuevaLista;
}

SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparar func) {

  SList nuevaLista = slist_crear();

  while (lista1 != NULL) {

    if (func(lista2, lista1->dato)) {
      nuevaLista = slist_agregar_final(nuevaLista, lista1->dato);

    }
    lista1 = lista1->sig;
  }

  return nuevaLista; 
}

SList slist_ordenar(SList lista, IntCmp func) {

  SNodo *cabeza = lista;

  SNodo *actual, *siguiente;
  int intercambio, comparar;

  do {
    intercambio = 0;
    actual = cabeza;

    while (actual->sig != NULL) {
      siguiente = actual->sig;
      comparar = func(actual->dato, siguiente->dato);

      if (comparar >= 0) {
        int temp = actual->dato;
        actual->dato = siguiente->dato;
        siguiente->dato = temp;
        intercambio = 1;
      }

      actual = actual->sig;
    }
  } while (intercambio);
  
  return cabeza;
}

SList slist_reverso(SList lista) {

  SList listaReversa = slist_crear();

  for (; lista != NULL; lista = lista->sig) {
    listaReversa = slist_agregar_inicio(listaReversa, lista->dato);
  }

  return listaReversa;
}

SList slist_intercalar(SList lista1, SList lista2) {

  SList listaIntercalada = lista1;

  for (int i = 1; lista2 != NULL; lista2 = lista2->sig, i += 2) {
    listaIntercalada = slist_insertar(listaIntercalada, lista2->dato, i);
  }


  return listaIntercalada;
}

SList slist_partir(SList lista) {

  size_t longitud = slist_longitud(lista);
  size_t indexFinalPrimeraMitad = (int)(longitud / 2);


  for (int i = !(longitud % 2); i <= indexFinalPrimeraMitad; lista = lista->sig, i++);
  
  return lista;

}

