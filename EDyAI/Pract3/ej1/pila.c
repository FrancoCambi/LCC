#include"pila.h"

Pila pila_crear(int capacidad) {

    Pila pila;

    pila->arr = arreglo_enteros_crear(capacidad);
    pila->ultimo = 0;

    return pila;
}

void pila_destruir(Pila pila) {

    arreglo_enteros_destruir(pila->arr);
    free(pila);
}

int pila_es_vacia(Pila pila) {

    return pila->ultimo == 0;
}

int pila_tope(Pila pila) {

    return arreglo_enteros_leer(pila->arr, pila->ultimo - 1);
}

void pila_apilar(Pila pila, int dato) {

    if (pila->ultimo == pila->arr->capacidad) {
        arreglo_enteros_ajustar(pila->arr, pila->arr->capacidad * 2);
    }

    arreglo_enteros_agregar(pila->arr, pila->ultimo, dato);
    pila->ultimo++;

}

void pila_desapilar(Pila pila) {

    pila->ultimo--;
}

void pila_imprimir(Pila pila) {

    for (int i = 0; i < pila->ultimo; i++) {
        printf("%d ", arreglo_enteros_leer(pila->arr, i));
    }
}