#include "matriz_bi.c"
#include<stdio.h>



int main(void) {

    Matriz *matriz = matriz_crear(2,2);

    matriz_escribir(matriz, 0, 0, 1);
    matriz_escribir(matriz, 0, 1, 2);
    matriz_escribir(matriz, 1, 0, 3);
    matriz_escribir(matriz, 1, 1, 4);

    printf("%lf ", matriz->arr[1][0]);

    return 0;
}