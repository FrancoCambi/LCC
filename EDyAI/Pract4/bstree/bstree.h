#ifndef __BSTREE_H__
#define __BSTREE_H__

#include<stddef.h>

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,  /** Inorden */
  BTREE_RECORRIDO_PRE, /** Preorden */
  BTREE_RECORRIDO_POST /** Postorden */
} BSTreeRecorrido;

typedef struct _BST_Nodo *BSTree;

/**
 * Retorna un arbol de busqueda binaria vacio.
 */
BSTree bstee_crear();

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree, FuncionDestructora);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree, void *, FuncionComparadora);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
BSTree bstree_insertar(BSTree, void *, FuncionCopiadora, FuncionComparadora);

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree, BSTreeRecorrido, FuncionVisitanteExtra,
                     void *extra);

/**
 * @brief Elimina un dato del BST
 * 
 * @param arbol 
 * @param dato 
 * @param comparar 
 * @param destruir 
 * @param copiar 
 * @return BSTree 
 */
BSTree bstree_eliminar(BSTree arbol, void* dato, FuncionComparadora comparar, FuncionDestructora destruir, FuncionCopiadora copiar);

/**
 * @brief Devuelve el k-esimo menor elemento del ABB
 * 
 * @param arbol 
 * @param k 
 * @return void* 
 */
void* bstree_k_esimo_menor(BSTree arbol, int k);

/**
 * @brief Valida si el arbol es un ABB
 * 
 * @param arbol 
 * @return int 
 */
int bstree_validar(BSTree arbol, FuncionComparadora comparar);

/**
 * @brief Devuelve el minimo elemento mayor a la cota
 * 
 * @param arbol 
 * @param cota 
 * @param comparar 
 * @return void* 
 */
void* bstree_cota_inferior(BSTree arbol, void* cota, FuncionComparadora comparar);

/**
 * @brief Recorre el BST e imprime los elementos en el intervalo [cota_inf, cota_sup]
 * 
 */
void bstree_recorrer_intervalo(BSTree arbol, void* cota_inf, void* cota_sup, FuncionVisitanteExtra visit, void* extra, FuncionComparadora comparar);

/**
 * @brief Crea un arbol 
 * 
 * @param bfs 
 * @param cantNodos 
 * @param copiar 
 * @return BSTree 
 */
BSTree bstree_bfs_to_tree(void** bfs, size_t cantNodos, FuncionCopiadora copiar, FuncionComparadora comparar);

#endif //__BSTREE_H__