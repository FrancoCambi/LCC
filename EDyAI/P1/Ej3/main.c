#include "main.h"

int main() {

    ArregloEnteros *arr = arreglo_enteros_crear(4);

    arreglo_enteros_escribir(arr, 0, 1);
    arreglo_enteros_escribir(arr, 1, 2);
    arreglo_enteros_escribir(arr, 2, 3);
    arreglo_enteros_escribir(arr, 3, 4);

    arreglo_enteros_eliminar(arr, 4);

    arreglo_enteros_imprimir(arr);
    
    return 0;
}