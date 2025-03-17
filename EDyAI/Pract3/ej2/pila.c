#include"pila.h"

Pila pila_crear() {
    
    Pila pila = glist_crear();

    return pila;
}

void pila_destruir(Pila pila, FuncionDestructora destruir) {

    glist_destruir(pila, destruir);
}

int pila_es_vacia(Pila pila) {

    return glist_vacia(pila);
}

void *pila_tope(Pila pila, FuncionCopia copiar) {
    return copiar(pila->data);
}

Pila pila_apilar(Pila pila, void *dato, FuncionCopia copiar) {

    pila = glist_agregar_inicio(pila, dato, copiar);

    return pila;
}

Pila pila_desapilar(Pila pila, FuncionDestructora destruir) {

    GNode *nodeToDelete = pila;

    pila = pila->next;
    destruir(nodeToDelete->data);
    free(nodeToDelete);

    return pila;
}

void pila_imprimir(Pila pila, FuncionVisitante visit) {

    glist_recorrer(pila, visit);
}

