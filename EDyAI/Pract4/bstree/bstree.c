#include"bstree.h"
#include <assert.h>
#include <stdlib.h>
#include<string.h>
#include<stdio.h>

/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */
struct _BST_Nodo {
  void *dato;
  struct _BST_Nodo *izq, *der;
};

/**
 * bstee_crear: Retorna un arbol de busqueda binaria vacio
 */
BSTree bstee_crear() { return NULL; }

/**
 * bstree_destruir: Destruye el arbol y sus datos
 */
void bstree_destruir(BSTree raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    bstree_destruir(raiz->izq, destr);
    bstree_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
}

/**
 * bstree_buscar: Retorna 1 si el dato se encuentra y 0 en caso
 * contrario
 */
int bstree_buscar(BSTree raiz, void *dato, FuncionComparadora comp) {
  if (raiz == NULL)
    return 0;
  else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
    return 1;
  else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    return bstree_buscar(raiz->izq, dato, comp);
  else // raiz->dato < dato
    return bstree_buscar(raiz->der, dato, comp);
}

/**
 * bstree_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad del arbol de busqueda binaria
 */
BSTree bstree_insertar(BSTree raiz, void *dato, FuncionCopiadora copia,
                       FuncionComparadora comp) {
  if (raiz == NULL) { // insertar el dato en un nuevo nodo
    struct _BST_Nodo *nuevoNodo = malloc(sizeof(struct _BST_Nodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copia(dato);
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
  } else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    raiz->izq = bstree_insertar(raiz->izq, dato, copia, comp);
  else if (comp(dato, raiz->dato) > 0) // raiz->dato < dato
    raiz->der = bstree_insertar(raiz->der, dato, copia, comp);
  // si el dato ya se encontraba, no es insertado
  return raiz;
}

/**
 * bstree_recorrer: Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree raiz, BSTreeRecorrido orden,
                     FuncionVisitanteExtra visita, void *extra) {
  if (raiz != NULL) {
    if (orden == BTREE_RECORRIDO_PRE)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->izq, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_IN)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->der, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_POST)
      visita(raiz->dato, extra);
  }
}

BSTree minDerecha(BSTree arbol) {
  while (arbol && arbol->izq != NULL) {
    arbol = arbol->izq;
  }
  return arbol;
}

BSTree bstree_eliminar(BSTree arbol, void* dato, FuncionComparadora comparar, FuncionDestructora destruir, FuncionCopiadora copiar) {

  if (arbol == NULL)
    return NULL;

  if (comparar(dato, arbol->dato) < 0) 
    arbol->izq = bstree_eliminar(arbol->izq, dato, comparar, destruir, copiar);
  else if (comparar(dato, arbol->dato) > 0)
    arbol->der = bstree_eliminar(arbol->der, dato, comparar, destruir, copiar);
  else {

    if (arbol->izq == NULL) {
      BSTree temp = arbol->der;
      destruir(arbol->dato);
      free(arbol);
      return temp;
    }
    else if (arbol->der == NULL) {
      BSTree temp = arbol->izq;
      destruir(arbol->dato);
      free(arbol);
      return temp;
    }

    BSTree temp = minDerecha(arbol->der);

    destruir(arbol->dato);
    arbol->dato = copiar(temp->dato);

    arbol->der = bstree_eliminar(arbol->der, arbol->dato, comparar, destruir, copiar);
  }

  return arbol;

}

void *bstree_k_esimo_menor_aux(BSTree arbol, int *k) {
   /* Si el árbol es vacío no hay elementos. */
  if (arbol == NULL)
    return NULL;  
  void *dato;
  /* Llamada recursiva al subárbol izquierdo. */
  dato = bstree_k_esimo_menor_aux(arbol->izq, k);
  if (dato != NULL)
    /* Si el dato no es NULL ya encontré el dato en el subárbol izquierdo. */
    return dato;
  /* Veo el nodo actual */
  if (*k == 0)
    /* Se está retornando la dirección del dato dentro del árbol.
    Si en el main de modifica o libera el dato devuelto por esta función,
    también se modificará dentro de esta estuctura. */
    return arbol->dato; 
  --(*k);
  /* Llamada recursiva al subárbol derecho */
  return bstree_k_esimo_menor_aux(arbol->der, k);
} 

void *bstree_k_esimo_menor(BSTree arbol, int k) {

  return bstree_k_esimo_menor_aux(arbol, &k);   
}

int bstree_validar_aux(BSTree arbol, BSTree low, BSTree high, FuncionComparadora comparar) {

  if (arbol == NULL)
    return 1;

  if ((low != NULL && comparar(arbol->dato, low->dato) <= 0) || 
      (high != NULL && comparar(arbol->dato, high->dato) >= 0))
        return 0;

  return bstree_validar_aux(arbol->izq, low, arbol, comparar) && 
         bstree_validar_aux(arbol->der, arbol, high, comparar);
}

int bstree_validar(BSTree arbol, FuncionComparadora comparar) {
  return bstree_validar_aux(arbol, NULL, NULL, comparar);  
}

static void bstree_cota_inferior_aux(BSTree arbol, void* cota, void** minimo, int* encontrado, FuncionComparadora comparar) {

  if (arbol == NULL)
    return;

  if (comparar(arbol->dato, cota) > 0) {
    if (*minimo == NULL)
      *minimo = arbol->dato;
    else
      *minimo = (comparar(*minimo, arbol->dato) >= 0) ? arbol->dato : *minimo;
    *encontrado = 1;
    bstree_cota_inferior_aux(arbol->izq, cota, minimo, encontrado, comparar);
  }
  
  bstree_cota_inferior_aux(arbol->der, cota, minimo, encontrado, comparar);
  
}

void* bstree_cota_inferior(BSTree arbol, void* cota, FuncionComparadora comparar){

  void* minimo = NULL;
  int encontrado = 0;

  bstree_cota_inferior_aux(arbol, cota, &minimo, &encontrado, comparar);

  if (encontrado)
    return minimo; // si lo encuentra devuelve el minimo encontrado

  return cota; // si no lo encuentra, devuelve la cota
}

void bstree_recorrer_intervalo(BSTree arbol, void* cota_inf, void* cota_sup, FuncionVisitanteExtra visit, void* extra, FuncionComparadora comparar) {

  if (arbol == NULL)
    return;
  
  if (comparar(arbol->dato, cota_inf) != 0) // Si esta en la cota inferior, no recorre el subarbol izquierdo 
                                            // ya que no estarán sus datos en el intervalo
    bstree_recorrer_intervalo(arbol->izq, cota_inf, cota_sup, visit, extra, comparar);
  if (comparar(arbol->dato, cota_inf) >= 0 && comparar(arbol->dato, cota_sup) <= 0)
    visit(arbol->dato, extra);
  if (comparar(arbol->dato, cota_sup) != 0) // si esta en la cota sup, no recorre el subarbol derecho 
                                           // ya que no estarán sus datos en el intervalo
    bstree_recorrer_intervalo(arbol->der, cota_inf, cota_sup, visit, extra, comparar);

}

static BSTree bstree_bfs_to_tree_aux(void** bfs, size_t cantNodos, size_t indexPadre, void* datoPadre, FuncionCopiadora copiar, FuncionComparadora comparar, int* flag) {

  if (indexPadre >= cantNodos)
    return NULL;
  if (datoPadre == NULL)
    return NULL;

  
  BSTree arbol = malloc(sizeof(struct _BST_Nodo));
  size_t indexIzq = indexPadre * 2 + 1;
  size_t indexDer = indexPadre * 2 + 2;

  void* datoIzq = indexIzq < cantNodos ?  bfs[indexIzq] : NULL;
  void* datoDer = indexDer < cantNodos ?  bfs[indexDer] : NULL;

  if (datoIzq && comparar(datoIzq, datoPadre) >= 0) {
    flag = 0;
    return NULL;
  }
  if (datoDer && comparar(datoDer, datoPadre) <= 0) {
    flag = 0;
    return NULL;
  }

  arbol->dato = copiar(datoPadre);
  arbol->izq = bstree_bfs_to_tree_aux(bfs, cantNodos, indexIzq, datoIzq, copiar, comparar, flag);
  arbol->der = bstree_bfs_to_tree_aux(bfs, cantNodos, indexDer, datoDer, copiar, comparar, flag);
  
  return arbol;

}
BSTree bstree_bfs_to_tree(void** bfs, size_t cantNodos, FuncionCopiadora copiar, FuncionComparadora comparar) {

  int flag = 1;
  BSTree arbolCreado = bstree_bfs_to_tree_aux(bfs, cantNodos, 0, bfs[0], copiar, comparar, &flag);

  if (flag)
    return arbolCreado;
  else
    // faltaria destruir el arbol que quedo a medias
    // o hacer otra funcion que primero determine si va a ser BST y despues lo cree <- (mejor opcion, 
    // para no tener que pasar la func destructora)
    return NULL;
}