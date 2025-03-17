#include"glist.h"
#include"pila.h"

GList glist_revertir(GList lista, FuncionCopia copia) {

    Pila pila = pila_crear();

    GNode *nodo;
    for(nodo = lista; nodo != NULL; nodo = nodo->next)
        pila_apilar(pila, nodo->data, copia);

    return pila->inicio;
}