#include"btreeg.h"

BTreeG btreeg_crear() { return NULL; }

void btreeg_destruir(BTreeG arbol, FuncionDestructora destruir) {

    if (arbol != NULL) {
        btreeg_destruir(arbol->left, destruir);
        btreeg_destruir(arbol->right, destruir);
        destruir(arbol->dato);
        free(arbol);
    }
}

int btreeg_empty(BTreeG arbol) { return arbol == NULL; }

BTreeG btreeg_unir(void* dato, BTreeG left, BTreeG right, 
                    FuncionCopia copiar) {

    BTreeG nuevoArbol = malloc(sizeof(struct _BTGNodo));
    assert(nuevoArbol != NULL);
    nuevoArbol->dato = copiar(dato);
    nuevoArbol->left = left;
    nuevoArbol->right = right;

    return nuevoArbol;
}

void btreeg_recorrer(BTreeG arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit) {

  if (btreeg_empty(arbol)) return;

  switch (orden) {

    case BTREE_RECORRIDO_PRE:
      visit(arbol->dato);
      btreeg_recorrer(arbol->left, orden, visit);
      btreeg_recorrer(arbol->right, orden, visit);
      break;

    case BTREE_RECORRIDO_IN:
      btreeg_recorrer(arbol->left, orden, visit);
      visit(arbol->dato);
      btreeg_recorrer(arbol->right, orden, visit);
      break;
    case BTREE_RECORRIDO_POST:
      btreeg_recorrer(arbol->left, orden, visit);
      btreeg_recorrer(arbol->right, orden, visit);
      visit(arbol->dato);
      break;
  }

}

BTreeG btreeg_copiar(BTreeG arbol, FuncionCopia copiar){
  if (arbol == NULL)
    return NULL;
  
  BTreeG copia = malloc(sizeof(struct _BTGNodo));
  copia->left = btreeg_copiar(arbol->left, copiar);
  copia->right = btreeg_copiar(arbol->right, copiar);

  copia->dato = copiar(arbol->dato);


  return copia;
}

static void btreeg_mirror_aux(BTreeG node) {
   if (node == NULL)
      return;
   
  BTreeG temp;
  btreeg_mirror_aux(node->left);
  btreeg_mirror_aux(node->right);
  temp = node->left;
  node->left = node->right;
  node->right = temp;
   
}
BTreeG btreeg_mirror(BTreeG arbol, FuncionCopia copiar) {
  BTreeG arbolMirror = btreeg_copiar(arbol, copiar); // deberia hacer una copia fisica y no de referencia del arbol

  btreeg_mirror_aux(arbolMirror);

  return arbolMirror;
}

int btreeg_nnodos(BTreeG arbol) {

  if (arbol == NULL) return 0;
  else return 1 + btreeg_nnodos(arbol->left) + btreeg_nnodos(arbol->right);

}

static int btreeg_completo_aux(BTreeG arbol, int index, int n) {
  if (arbol == NULL)
    return 1;

  if (index >= n)
    return 0;
  
  return btreeg_completo_aux(arbol->left, index * 2 + 1, n) &&
         btreeg_completo_aux(arbol->right, index * 2 + 2, n);
}
int btreeg_completo(BTreeG arbol) {

  int n = btreeg_nnodos(arbol);

  return btreeg_completo_aux(arbol, 0, n);
}
