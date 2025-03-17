#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
    printf("%d ", dato);
}

int main(int argc, char *argv[]) {

    DList* lista = dlist_crear();

    lista = dlist_agregar_final(lista, 1);
    lista = dlist_agregar_final(lista, 2);
    lista = dlist_agregar_final(lista, 3);

    dlist_recorrer(lista, imprimir_entero, DLIST_RECORRIDO_HACIA_ATRAS);

    return 0;
}