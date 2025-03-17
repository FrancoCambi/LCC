#include"pila.h"

Pila pila_crear() {

    Pila pila = malloc(sizeof(Pila));

    pila->inicio = glist_crear();

    return pila;
}

void pila_destruir(Pila pila, FuncionDestructora destuir) {

    glist_destruir(pila->inicio, destuir);
    free(pila);
}

int pila_es_vacia(Pila pila) {

    return glist_vacia(pila->inicio);
}

void *pila_tope(Pila pila) {

    return pila->inicio->data;
}

void pila_apliar(Pila pila, void *dato, FuncionCopia copia) {

    pila->inicio = glist_agregar_inicio(pila->inicio, dato, copia);
}

void pila_desapilar(Pila pila) {

    GNode *nodoALiberar = pila->inicio;

    pila->inicio = pila->inicio->next;
    free(nodoALiberar);
}

void pila_imprimir(Pila pila, FuncionVisitante visit) {

    glist_recorrer(pila->inicio, visit);
}