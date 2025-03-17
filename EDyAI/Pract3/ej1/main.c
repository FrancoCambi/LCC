#include"pila.h"

int main(void) {

    Pila pila = pila_crear(3);

    pila_apilar(pila, 1);
    pila_apilar(pila, 2);
    pila_apilar(pila, 3);
    pila_apilar(pila, 4);

    pila_desapilar(pila);
    pila_desapilar(pila);

    pila_apilar(pila, 5);
    pila_apilar(pila, 7);

    pila_imprimir(pila);

    return 0;
}