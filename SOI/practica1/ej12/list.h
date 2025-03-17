#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef struct _SNodo {
  char * key;
  char * value;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, char * key, char * value);

/**
 * Borra un nodo de la lista si encuentra la key.
 */
SList slist_borrar_par(SList lista, char * key);

/**
 * Buscar value segun la key 
 */
char * slist_buscar(SList lista, char * key);

void slist_imprimir(SList lista);
#endif /* __SLIST_H__ */
