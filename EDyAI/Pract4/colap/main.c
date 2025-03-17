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
static int comparar_dato(Dato dato1, Dato dato2) {

  return dato1->prioridad - dato2->prioridad;
}

int main(void) {

  ColaP cola = cola_prioridad_crear(4, comparar_dato);

  /*int a = 3;
  int b = 5;
  int c = 2;
  int d = 1;
  
  printf("Agregando...\n");
  cola_prioridad_insertar(cola, &a, 4, copiar_puntero_entero);
  cola_prioridad_insertar(cola, &b, 3, copiar_puntero_entero);
  cola_prioridad_insertar(cola, &c, 2, copiar_puntero_entero);
  cola_prioridad_insertar(cola, &d, 1, copiar_puntero_entero);*/

  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0; i < 10; i++) {
    cola_prioridad_insertar(cola, &arr[i], arr[i], copiar_puntero_entero);
  }

  printf("Recorrido: ");
  cola_prioridad_recorrer(cola, imprimir_puntero_entero);
  puts("");

  puts("Eliminando..");
  cola_prioridad_eliminar_maximo(cola, destruir_puntero_entero);

  puts("Recorrido: ");
  cola_prioridad_recorrer(cola, imprimir_puntero_entero);

  puts("\nDestruyendo...");
  cola_prioridad_destruir(cola, destruir_puntero_entero);

  puts("Todo ok! :D");
    

  return 0;
}