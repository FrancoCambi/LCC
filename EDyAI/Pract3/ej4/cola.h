#ifndef __COLA_H__
#define __COLA_H__

#include"slist.h"

typedef SList* Cola;

/**
 * @brief Devuelve una cola vacia
 * 
 * @return Cola 
 */
Cola cola_crear();

/**
 * @brief Destruye una cola
 * 
 * @param cola 
 */
void cola_destruir(Cola cola, FuncionDestructora destruir);

/**
 * @brief Determina si una cola está vacia
 * 
 * @param cola 
 * @return int 
 */
int cola_es_vacia(Cola cola);

/**
 * @brief Devuelve el elemento al inicio de la cola (sin eliminarlo).
 * 
 * @param cola 
 * @return void* 
 */
void *cola_inicio(Cola cola, FuncionCopia copiar);
    
/**
 * @brief Agrega un elemento al final de la cola
 * 
 * @param cola 
 * @param copiar 
 * @return Cola 
 */
Cola cola_encolar(Cola cola, void* dato, FuncionCopia copiar);

/**
 * @brief Elimina el primer elemento de la cola
 * 
 * @param cola 
 * @param destruir 
 * @return Cola 
 */
Cola cola_desencolar(Cola cola, FuncionDestructora destruir);

/**
 * @brief Imprime una cola.
 * 
 * @param cola 
 * @param visit 
 */
void cola_imprimir(Cola cola, FuncionVisitante visit);

#endif