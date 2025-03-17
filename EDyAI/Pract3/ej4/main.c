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
    
    Cola cola = cola_crear();

    int *num1 = crear_int(5);
    int *num2 = crear_int(3);
    int *num3 = crear_int(8);
    cola = cola_encolar(cola, num1, (FuncionCopia)copiar);
    cola = cola_encolar(cola, num2, (FuncionCopia)copiar);
    cola = cola_encolar(cola, num3, (FuncionCopia)copiar);
    cola = cola_desencolar(cola, (FuncionDestructora)destruir);

    imprimir(cola_inicio(cola, (FuncionCopia) copiar));

    cola_imprimir(cola, (FuncionVisitante)imprimir);

    cola_destruir(cola, (FuncionDestructora)destruir);

    return 0;
}