#include "slist.h"
#include <stdlib.h>

DList* dlist_crear() {
    DList* lista = malloc(sizeof(DList));

    lista->primero = NULL;
    lista->ultimo = NULL;

    return lista;
}

DList* dlist_agregar_inicio(DList* lista, int dato) {
    DNodo* nodo = malloc(sizeof(DNodo));
    nodo->dato = dato;
    nodo->sig = lista->primero;
    nodo->ant = NULL;
   
    if (lista->ultimo == NULL) {
        lista->ultimo = nodo;
    }

    lista->primero = nodo;

    return lista;
}

DList* dlist_agregar_final(DList* lista, int dato) {
    DNodo* nodo = malloc(sizeof(DNodo));
    nodo->dato = dato;
    nodo->sig = NULL;
    nodo->ant = lista->ultimo;

    if (lista->ultimo != NULL) {
        lista->ultimo->sig = nodo;
    }

    if (lista->primero == NULL) {
        lista->primero = nodo;
    }

    lista->ultimo = nodo;

    return lista;
}

void dlist_recorrer(DList *lista, FuncionVisitante func, DListOrdenDeRecorrido orden) {
    /*DNodo* nodo = orden == DLIST_RECORRIDO_HACIA_ADELANTE ? lista->primero : lista->ultimo;

    for (; nodo != NULL; nodo = DLIST_RECORRIDO_HACIA_ADELANTE ? nodo->sig : nodo->ant)
        func(nodo->dato);*/

    DNodo* nodo;
    if (orden == DLIST_RECORRIDO_HACIA_ADELANTE) {
        nodo = lista->primero;

        for (; nodo != NULL; nodo = nodo->sig)
            func(nodo->dato);
    }
    else {
        nodo = lista->ultimo;

        for (; nodo != NULL; nodo = nodo->ant)
            func(nodo->dato);
    }
}