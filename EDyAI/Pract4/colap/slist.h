#ifndef __SLIST_H__
#define __SLIST_H__

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

typedef struct _SNodo {
    void *dato;
    struct _SNodo *sig;
}SNodo;

typedef struct _SList {
    SNodo *head;
    SNodo *tail;
}SList;

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void *dato);
typedef int (*FuncionComparadora)(void *data1, void *data2);

/**
 * @brief Devuelve una lista vacia
 * 
 */
SList* slist_crear();

/**
 * @brief Destruye una lista
 * 
 * @param lista 
 * @param destruir 
 */
void slist_destruir(SList *lista, FuncionDestructora destruir);

/**
 * @brief Determina si una lista es vacia
 * 
 * @param lista 
 * @return int 
 */
int slist_vacia(SList *lista);

/**
 * @brief Agrega un elemento al final de una lista
 * 
 * @param lista 
 * @param dato 
 * @param copiar 
 * @return SList* 
 */
SList* slist_agregar_final(SList *lista, void* dato, FuncionCopia copiar);

/**
 * @brief Recorre una lista aplicando la funcion visitante a cada dato
 * 
 * @param lista 
 * @param visit 
 */
void slist_recorrer(SList *lista, FuncionVisitante visit);

#endif