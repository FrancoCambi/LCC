#include<stdio.h>
#include<stdlib.h>
#include "ej3.h"


ArregloEnteros *arreglo_enteros_crear(int capacidad) {

    ArregloEnteros *arreglo = malloc(sizeof(ArregloEnteros));

    if (!arreglo) { //Si falla la asignación de memoria
        return NULL;
    }

    arreglo->direccion = malloc(sizeof(int) * capacidad);

    if (!arreglo->direccion) { //Si falla la asignación de memoria
        free(arreglo);
        return  NULL;
    }
    
    arreglo->capacidad = capacidad;

    return arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros *arreglo) {

    // Se chequea que el arreglo no sea null antes de liberar la memoria
    if (arreglo) {
        free(arreglo->direccion);
        free(arreglo);
    }
}

int arreglo_enteros_leer(ArregloEnteros *arreglo, int pos) {

    return arreglo->direccion[pos];
}  

void arreglo_enteros_escribir(ArregloEnteros *arreglo, int pos, int dato) {
    if (arreglo && pos >= 0 && pos < arreglo->capacidad)
        arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros *arreglo) {

    return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros *arreglo) {

    // Si es vacio, solo imprime llaves vacias
    printf("{");

    if (arreglo->capacidad != 0) {
        for (int i = 0; i < arreglo->capacidad - 1; i++)
            printf("%d, ", arreglo->direccion[i]);
    
        printf("%d", arreglo->direccion[arreglo->capacidad - 1]);
    }

    printf("}");
}

void arreglo_enteros_ajustar(ArregloEnteros *arreglo, int capacidad) {

    if (arreglo && capacidad >= 0 && capacidad <= arreglo->capacidad) {

        // Reajuste de la memoria dinamica
        arreglo->direccion = realloc(arreglo->direccion, sizeof(int) * capacidad);

        arreglo->capacidad = capacidad;
    }

}

void arreglo_enteros_insertar(ArregloEnteros *arreglo, int pos, int dato) {

    // Si pos va mas allá de una posición a la derecha de la ultima, se cambia
    // pos para que se agrege el dato al final del arreglo
    if (pos > arreglo->capacidad)
        pos = arreglo->capacidad;
    
    // Si pos es menor a 0, cambia pos para agregar el dato en la primer posición.
    else if (pos < 0)
        pos = 0;

    // Reajustar la memoria dinamica con un espacio más
    arreglo->direccion = realloc(arreglo->direccion, sizeof(int) * (arreglo->capacidad + 1));

    // Correr todos los espacios de derecha a izquierda
    for (int i = arreglo->capacidad; i > pos; i--) {
        arreglo->direccion[i] = arreglo->direccion[i - 1];
    }

    // Ajustar la capacidad
    arreglo->capacidad = arreglo->capacidad + 1;

    // Agregar nuevo dato
    arreglo->direccion[pos] = dato;

}

void arreglo_enteros_eliminar(ArregloEnteros *arreglo, int pos) {


    if (pos >= 0 && pos < arreglo->capacidad) {

        // Correr todos los espacios izquierda a derecha
        for (int i = pos; i < arreglo->capacidad - 1; i++) {
            arreglo->direccion[i] = arreglo->direccion[i + 1];
        }
    
        // Reajustar la memoria dinamica con un espacio menos
        arreglo->direccion = realloc(arreglo->direccion, sizeof(int) * (arreglo->capacidad - 1));


        // Ajustar la capacidad
        arreglo->capacidad = arreglo->capacidad - 1;
    }
}