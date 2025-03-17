#ifndef __BTREEG_H__
#define __BTREEG_H__

#include <assert.h>
#include <stdlib.h>
#include<stdio.h>

typedef void (*FuncionVisitante)(void* dato);
typedef void (*FuncionDestructora)(void* dato);
typedef void *(*FuncionCopia)(void* dato);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

struct _BTGNodo {
    void *dato;
    struct _BTGNodo *left;
    struct _BTGNodo *right;

};

typedef struct _BTGNodo* BTreeG;

/**
 * @brief Devuelve un arbol general vacio
 * 
 */
BTreeG btreeg_crear();

/**
 * @brief Destruccin del arbol
 * 
 */
void btreeg_destruir(BTreeG arbol, FuncionDestructora destruir);

/**
 * @brief Indica si el arbol es vacio
 * 
 */
int btreeg_empty(BTreeG arbol);

/**
 * @brief Crea un nuevo arbol, con el dato dado en el nodo raiz, 
 * y los subarboles dados a izquierda y derecha.
 * 
 */
BTreeG btreeg_unir(void* dato, BTreeG left, BTreeG right, FuncionCopia copiar);

/**
 * @brief Recorrido del arbol, utilizando la funcion y el metodo pasados
 * 
 */
void btreeg_recorrer(BTreeG arbol, BTreeOrdenDeRecorrido orden, 
                    FuncionVisitante visit);

/**
 * @brief Crea una copia de un arbol
 * 
 */
BTreeG btreeg_copiar(BTreeG arbol, FuncionCopia copiar);

/**
 * @brief Crea el espejo de un arbol binario en el segundo parametro
 * 
 * @param arbol 
 * @return BTreeG 
 */
BTreeG btreeg_mirror(BTreeG arbol, FuncionCopia copiar);

/**
 * @brief Cuenta la cantidad de nodos de un arbol
 * 
 * @param arbol 
 * @return int 
 */
int btreeg_nnodos(BTreeG arbol);

/**
 * @brief determina si un arbol binario es completo
 * 
 */
int btreeg_completo(BTreeG arbol);


#endif