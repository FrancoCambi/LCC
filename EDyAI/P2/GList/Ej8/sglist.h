#ifndef __SGLIST_H__
#define __SGLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante)(void *data);
typedef void *(*FuncionCopia)(void *data);
typedef int (*FuncionComparadora)(void *data1, void *data2);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode* SGList;

// Retorna una lista vacia
SGList sglist_crear();

// Destruye una lista ordenada 
void sglist_destruir(SGList lista, FuncionDestructora destruir);

/**
 * Agrega un elemento al inicio de la lista.
 */
SGList sglist_agregar_inicio(SGList lista, void *dato, FuncionCopia copiar);

// Determina si una lista ordenada está vacia
int sglist_vacia(SGList lista);

// Recorre la lista aplicando la funcion visitante a cada uno
void sglist_recorrer(SGList lista, FuncionVisitante func);

// Inserta un nuevo dato en la lista ordenada.
SGList sglist_insertar(SGList lista, void *data, FuncionCopia copiar, FuncionComparadora comparar);

int sglist_buscar(SGList lista, void *data, FuncionComparadora comparar);

SGList sglist_arr(void **arr, int longitud, FuncionCopia copiar, FuncionComparadora comparar);

#endif