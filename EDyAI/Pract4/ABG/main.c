#include"main.h"
#include<stdio.h>

static void destruir_puntero_entero(void* i) { free(i); }
static void imprimir_puntero_entero(void* i) {
  printf("%d ", *(int*)i);
}

static void* copiar_puntero_entero(void* i) {
  int* p = malloc(sizeof(int));
  *p = *(int*)i;
  return p;
}


int main(void) {

    int num1 = 4;
    int num2 = 2;
    int num3 = 3;
    int num4 = 1;
    int num5 = 7;

    BTreeG l1 = btreeg_unir(&num4, btreeg_unir(&num5, btreeg_crear(), btreeg_crear(), copiar_puntero_entero), btreeg_crear(), copiar_puntero_entero);
    BTreeG l = btreeg_unir(&num2, l1, btreeg_crear(), copiar_puntero_entero);
    BTreeG r = btreeg_unir(&num3, btreeg_crear(), btreeg_crear(), copiar_puntero_entero);
    BTreeG arbol = btreeg_unir(&num1, l, r, copiar_puntero_entero);

    puts("Recorrido arbol: ");
    btreeg_recorrer(arbol, BTREE_RECORRIDO_IN, imprimir_puntero_entero);

    printf("%d\n", btreeg_cota_inferior(arbol, 5));

    //BTreeG arbolMirror = btreeg_mirror(arbol, copiar_puntero_entero);
    //puts("\nRecorrido arbolMirror: ");
    //btreeg_recorrer(arbolMirror, BTREE_RECORRIDO_IN, imprimir_puntero_entero);

    btreeg_destruir(arbol, destruir_puntero_entero);
    //btreeg_destruir(arbolMirror, destruir_puntero_entero);

    return 0;
}