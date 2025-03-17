#ifndef __BTREE_H__
#define __BTREE_H_

typedef void (*FuncionVisitante)(int dato);
typedef void (*FuncionVisitanteExtra)(int dato, void* extra);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);

/**
 * Recorrido del arbol utilizando preorden y de forma iterativa
*/
void btree_recorrer_pre_iter(BTree arbol, FuncionVisitante visit);

/**
 * Cuenta la cantidad de nodos de un arbol
*/
int btree_nnodos(BTree arbol);

/**
 * Busca un elemento en el arbol y devuelve 1 si lo encuentra
*/
int btree_buscar(BTree arbol, int dato);

/**
 * Devuelve una copia del arbol dado
*/
BTree btree_copiar(BTree arbol);

/**
 * Devuelve la altura de un arbol.
*/
int btree_altura(BTree arbol);

/**
 * Devuelve la cantidad de nodos que se encuentran en la profundidad dada
*/
int btree_nnodos_profundidad(BTree arbol, int profundidad);

/**
 * Devuelve la profundidad del nodo que contiene al dato
*/
int btree_profundidad(BTree arbol, int dato);

/**
 * @brief Devuelve la suma de todos los nodos de un arbol binario.
 * 
 * @param arbol 
 * @return int 
 */
int btree_sumar(BTree arbol);

/**
 * @brief Recorre el arbol binario aplicando la funcion
 * 
 * @param tree 
 */
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void* extra);

/**
 * @brief recorre solo una profundidad determinada del arbol aplicando la funcion a los datos
 * 
 * @param arbol 
 * @param visit 
 * @param profundidad 
 */
void btree_recorrer_profundidad(BTree arbol, FuncionVisitante visit, int profundidad);

/**
 * @brief Recorre un arbol usando el algoritmo de busqueda por extension
 * 
 * @param arbol 
 * @param visit 
 */
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit);

#endif /* __BTREE_H__ */
