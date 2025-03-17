#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>


typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef struct SList {
  SNodo *primero;
  SNodo *ultimo;
} SList;

typedef void (*FuncionVisitante) (int dato);
typedef int (*FuncionComparar) (SList lista, int dato);
typedef int (*IntCmp) (int dato1, int dato2);


/**
 * Devuelve una lista vacía.
 */
SList* slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList* slist_agregar_final(SList* lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList* slist_agregar_inicio(SList* lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

/**
 * Devuelve la longitud de una lista
*/
size_t slist_longitud(SList lista);

/**
 * Devuelve la concatenaciòn de dos listas modificando la primera.
*/
SList slist_concatenar(SList lista1, SList lista2);

/**
 * Inserta un dato en una lista en una posiciòn arbitraria
*/
SList slist_insertar(SList lista, int dato, size_t pos);


/**
 * Elimina un dato en una posiciòn arbitraria.
*/
SList slist_eliminar(SList lista, size_t pos);

/**
 * Determina si un elemento està en la lista.
*/
int slist_contiene(SList lista, int dato);

/**
 * Devuelve el ìndice de ocurrencia de un dato en la lista.
*/
size_t slist_indice(SList lista, int dato);

/**
 * Devuelve la intersecciòn de dos listas.
*/
SList slist_intersecar(SList lista1, SList lista2);

/**
 * Devuelve la intersecciòn de dos listas segùn una funciòn comparar.
*/
SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparar func);

/**
 * Ordena una lista de acuerdo al criterio dado por la funciòn pasada.
*/
SList slist_ordenar(SList lista, IntCmp func);

/**
 * Devuelve el reverso de una lista
*/
SList slist_reverso(SList lista);

/*
 * Intercala los elementos de dos listas
*/
SList slist_intercalar(SList lista1, SList lista2);

/*
 *Parte una lista a la mitad y devuelve la segunda mitad de longitud n
*/
SList slist_partir(SList lista);


#endif /* __SLIST_H__ */
