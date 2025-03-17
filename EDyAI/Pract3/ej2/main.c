#include"main.h"

void imprimir(int *num) {
    printf("%d ", *num);
}

void destruir(int *num) {
    free(num);
}

int *copiar(int *num) {

    int *numCopia = num;

    return numCopia;
}

int *crear_int(int num) {

    int *nuevoInt = malloc(sizeof(int));

    *nuevoInt = num;

    return nuevoInt;
}

int main(void) {
    
    Pila pila = pila_crear();

    int *num1 = crear_int(5);
    int *num2 = crear_int(3);
    int *num3 = crear_int(8);
    pila = pila_apilar(pila, num1, (FuncionCopia)copiar);
    pila = pila_apilar(pila, num2, (FuncionCopia)copiar);
    pila = pila_apilar(pila, num3, (FuncionCopia)copiar);


    pila_imprimir(pila, (FuncionVisitante)imprimir);
    
    pila_destruir(pila, (FuncionDestructora)destruir);

    return 0;
}