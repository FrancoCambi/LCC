#ifndef __PILA_H__
#define __PILA_H__

#include"glist.h"

typedef GList Pila;

/**
 * @brief Devuelve una pila vacia
 * 
 * @return Pila 
 */
Pila pila_crear();

/**
 * @brief Destruye una pila.
 * 
 * @param pila 
 * @param destruir 
 */
void pila_destruir(Pila pila, FuncionDestructora destruir);

/**
 * @brief Determina si una pila es vacia
 * 
 * @param pila 
 * @return int 
 */
int pila_es_vacia(Pila pila);

/**
 * @brief Devuelve el elemento tope de la pila
 * 
 * @param pila 
 * @param copiar 
 * @return void* 
 */
void *pila_tope(Pila pila, FuncionCopia copiar);

/**
 * @brief Agrega un elemento a la pila
 * 
 * @param pila 
 * @param dato 
 * @param copiar 
 * @return Pila 
 */
Pila pila_apilar(Pila pila, void *dato, FuncionCopia copiar);

/**
 * @brief Elimina el elemento tope de la pila
 * 
 * @param pila 
 * @param destruir 
 * @return Pila 
 */
Pila pila_desapilar(Pila pila, FuncionDestructora destruir);

/**
 * @brief Imprime una cola
 * 
 * @param pila 
 * @param visit 
 */
void pila_imprimir(Pila pila, FuncionVisitante visit);

#endif