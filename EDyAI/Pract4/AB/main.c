#include"main.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

static void imprimir_entero_extra(int data, void* extra) {
  int *x = (int*)extra;
  printf("%d | %d", data, *x);
}

int main() {
  BTree ll = btree_unir(1, btree_unir(7, btree_crear(), btree_crear()), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);

  int x = 7;
  btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  btree_destruir(raiz);

  return 0;
}
