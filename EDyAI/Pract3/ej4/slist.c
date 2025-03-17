#include"slist.h"

SList *slist_crear() {
    SList *lista = malloc(sizeof(SList));

    lista->head = NULL;
    lista->tail = NULL;

    return lista;
}

void slist_destruir(SList *lista, FuncionDestructora destruir) {

    SNodo *nodeToDelete;
    while (lista->head != NULL) {
        nodeToDelete = lista->head;
        lista->head = lista->head->sig;
        destruir(nodeToDelete->dato);
        free(nodeToDelete);
    }

    free(lista);

}

int slist_vacia(SList *lista) {
    
    return (lista->head == NULL && lista->tail == NULL);
}

SList *slist_agregar_final(SList *lista, void *dato, FuncionCopia copiar) {

    SNodo *nodo = malloc(sizeof(SNodo));
    assert(nodo != NULL);

    nodo->dato = copiar(dato);
    nodo->sig = NULL;

    if (lista->tail != NULL)
        lista->tail->sig = nodo;
    if (lista->head == NULL)
        lista->head = nodo;

    lista->tail = nodo;

    return lista;
}

void slist_recorrer(SList *lista, FuncionVisitante visit) {

    for (SNodo *nodo = lista->head; nodo != NULL; nodo = nodo->sig)
        visit(nodo->dato);
}