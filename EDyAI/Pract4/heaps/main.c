#include"main.h"

static void* copiar_puntero_entero(void* i) {
  int* p = malloc(sizeof(int));
  *p = *(int*)i;
  return p;
}
static int comparar_puntero_entero(void* i1, void* i2) {
  return (*(int*)i1 - *(int*)i2);
}
static void destruir_puntero_entero(void* i) { free(i); }
static void imprimir_puntero_entero(void* i) {
  printf("%d ", *(int*)i);
}

int main(void) {

    BHeap heap = bheap_crear(2, comparar_puntero_entero);

    int a = 2;
    int b = 3;
    int c = 4;
    int d = 5;
    bheap_insertar(heap, &a, copiar_puntero_entero);
    bheap_insertar(heap, &b, copiar_puntero_entero);
    bheap_insertar(heap, &c, copiar_puntero_entero);
    bheap_insertar(heap, &d, copiar_puntero_entero);
    printf("Recorrido: ");
    bheap_recorrer(heap, imprimir_puntero_entero);
    puts("");

    bheap_eliminar(heap, &a, destruir_puntero_entero);
    printf("Elimnando 5.. -> Recorrido: ");
    bheap_recorrer(heap, imprimir_puntero_entero);

    bheap_destruir(heap, destruir_puntero_entero);

    return 0;
}