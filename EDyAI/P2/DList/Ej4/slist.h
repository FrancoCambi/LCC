#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);

typedef struct _DNodo {
    int dato;
    struct _DNodo* sig;
    struct _DNodo* ant;
} DNodo;

typedef struct {
    DNodo* primero;
    DNodo* ultimo;
} DList;

typedef enum {
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

/**
 * @brief Crea una lista doblemente enlazada con memoria dinámica
 * 
 * @return DList* 
 */
DList* dlist_crear();

/**
 * @brief Agrega un elemento al principio de una DList
 * 
 * @param lista 
 * @param dato 
 * @return DList* 
 */
DList* dlist_agregar_inicio(DList* lista, int dato);

/**
 * @brief Agrega un elemento al final de una DList
 * 
 * @param lista 
 * @param dato 
 * @return DList* 
 */
DList* dlist_agregar_final(DList* lista, int dato);

/**
 * @brief Recorre una lista en un orden dado y aplica una función a cada dato
 * 
 * @param lista 
 * @param func 
 */
void dlist_recorrer(DList *lista, FuncionVisitante func, DListOrdenDeRecorrido orden);

#endif