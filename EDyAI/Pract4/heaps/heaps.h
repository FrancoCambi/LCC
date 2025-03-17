#ifndef __HEAPS_H__
#define __HEAPS_H__

#include"slist.h"

typedef struct _BHeap {
    void **arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comparar;
} *BHeap;

/*
Crea un heap vacio con capacidad y funcion comparadora dadas*/
BHeap bheap_crear(int, FuncionComparadora);

/**
 * @brief Destruye un heap
 * 
 */
void bheap_destruir(BHeap, FuncionDestructora);

/**
 * @brief Determina si un heap es vacio
 * 
 */
int bheap_vacio(BHeap);

/**
 * @brief Recorre los nodos usando busqueda por extension aplicando la funcion dada en cada elemento
 * 
 */
void bheap_recorrer(BHeap, FuncionVisitante);

/**
 * @brief Agrega un alemento al heap
 * 
 */
void bheap_insertar(BHeap, void*, FuncionCopia);

/**
 * @brief Elimina un elemento del heap
 * 
 */
void bheap_eliminar(BHeap, void*, FuncionDestructora);

#endif