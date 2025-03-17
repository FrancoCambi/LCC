#include "btree.h"
#include <assert.h>
#include <stdlib.h>

struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit) {

  if (btree_empty(arbol)) return;

  switch (orden) {

    case BTREE_RECORRIDO_PRE:
      visit(arbol->dato);
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
      break;

    case BTREE_RECORRIDO_IN:
      btree_recorrer(arbol->left, orden, visit);
      visit(arbol->dato);
      btree_recorrer(arbol->right, orden, visit);
      break;
    case BTREE_RECORRIDO_POST:
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
      visit(arbol->dato);
      break;
  }

}

void btree_recorrer_pre_iter(BTree arbol, FuncionVisitante visit) {


}

int btree_nnodos(BTree arbol) {

  if (arbol == NULL) return 0;
  else return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);

}

int btree_buscar(BTree arbol, int dato) {

  if (btree_empty(arbol))
    return 0;
  
  else if (arbol->dato == dato) 
    return 1;
  
  else 
    return btree_buscar(arbol->left, dato) + btree_buscar(arbol->right, dato);

}

BTree btree_copiar(BTree arbol) {

  BTree nuevoArbol = malloc(sizeof(struct _BTNodo));

  nuevoArbol = btree_unir(arbol->dato, arbol->left, arbol->right);

  return nuevoArbol;
}

int btree_altura(BTree arbol) {

  if (btree_empty(arbol))
    return -1;

  // Si es hoja
  if (arbol->left == NULL && arbol->right == NULL)
    return 0;

  int alturaLeft = 1 + btree_altura(arbol->left);
  int alturaRight = 1 + btree_altura(arbol->right);

  return alturaLeft > alturaRight ? alturaLeft : alturaRight;

}

int btree_nnodos_profundidad(BTree arbol, int profundidad) {

  if (btree_empty(arbol))
    return 0;
  if (profundidad == 0)
    return 1;

  return (btree_nnodos_profundidad(arbol->left, profundidad - 1) + 
    btree_nnodos_profundidad(arbol->right, profundidad - 1));
}

int btree_profundidad(BTree arbol, int dato) {


  if (arbol == NULL)
    return -1;

  if (arbol->dato == dato)
    return 0;

  return 1 + (btree_buscar(arbol->left, dato) == 1 ? btree_profundidad(arbol->left, dato) : btree_profundidad(arbol->right, dato));
  
}

int btree_sumar(BTree arbol) {

  if (arbol == NULL)
    return 0;

  return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);

}

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void* extra) {

  if (btree_empty(arbol)) return;

  switch (orden) {

    case BTREE_RECORRIDO_PRE:
      visit(arbol->dato, extra);
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
      break;

    case BTREE_RECORRIDO_IN:
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      visit(arbol->dato, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
      break;
    case BTREE_RECORRIDO_POST:
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
      visit(arbol->dato, extra);
      break;
  }

}

void btree_recorrer_profundidad(BTree arbol, FuncionVisitante visit, int profundidad) {

  if (arbol == NULL)  
    return;

  if (profundidad == 0)
    visit(arbol->dato);

  btree_recorrer_profundidad(arbol->left, visit, profundidad - 1);
  btree_recorrer_profundidad(arbol->right, visit, profundidad - 1);

}

void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit) {

  size_t altura = btree_altura(arbol);

  for (int i = 0; i <= altura; i++) {
    btree_recorrer_profundidad(arbol, visit, i);
  }
}