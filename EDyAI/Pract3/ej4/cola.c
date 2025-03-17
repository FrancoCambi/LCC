#include"cola.h"

Cola cola_crear() {

    Cola cola = slist_crear();

    return cola;
}

void cola_destruir(Cola cola, FuncionDestructora destruir) {

    slist_destruir(cola, destruir);
}

int cola_es_vacia(Cola cola) {

    return slist_vacia(cola);
}

void *cola_inicio(Cola cola, FuncionCopia copiar) {

    return copiar(cola->head->dato);
}

Cola cola_encolar(Cola cola, void* dato, FuncionCopia copiar) {

    cola = slist_agregar_final(cola, dato, copiar);

    return cola;
}

Cola cola_desencolar(Cola cola, FuncionDestructora destruir) {
    
    SNodo* nodeToDelete = cola->head;

    if (cola->head == cola->tail)
        cola->tail = NULL;

    cola->head = cola->head->sig;
    destruir(nodeToDelete->dato);
    free(nodeToDelete);

    return cola;
}

void cola_imprimir(Cola cola, FuncionVisitante visit) {

    slist_recorrer(cola, visit);
}