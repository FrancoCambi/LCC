#ifndef __COLAP_H__
#define __COLAP_H__

#include"heaps.h"

/* Estructura de tipo dato que guarda un void* y una prioridad */
typedef struct _Dato {
    void* val;
    int prioridad;
}*Dato;

typedef int (*FuncionComparadoraDato)(Dato, Dato);

typedef struct _ColaP {
    Dato* arr;
    int capacidad;
    int ultimo;
    FuncionComparadoraDato comparar;
} *ColaP;

/**
 * @brief Crea una cola de prioridad
 * 
 */
ColaP cola_prioridad_crear(int, FuncionComparadoraDato);

/**
 * @brief Destruye una cola de prioridad
 * 
 */
void cola_prioridad_destruir(ColaP, FuncionDestructora);

/**
 * @brief Determina si la cola de prioridad es vacia
 * 
 */
int cola_prioridad_es_vacia(ColaP);

/**
 * @brief Recorre una cola de prioridad
 * 
 */
void cola_prioridad_recorrer(ColaP, FuncionVisitante);

/**
 * @brief Retorna el elemento prioritario de la cola
 * 
 */
void* cola_prioridad_maximo(ColaP);

/**
 * @brief Elimina el elemento prioritario de la cola
 * 
 */
void cola_prioridad_eliminar_maximo(ColaP, FuncionDestructora);

/**
 * @brief Inserta un elemento en la cola con determinada prioridad
 * 
 */
void cola_prioridad_insertar(ColaP, void*, int, FuncionCopia);

#endif