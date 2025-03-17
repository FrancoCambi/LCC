#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "locker.h"

#define M 5 // CANTIDAD_ESCRITORES
#define N 5 // CANTIDAD_LECTORES
#define ARRLEN 10240
#define TIEMPO_DE_ESPERA 2 // random % TIEMPO_DE_ESPERA
#define TIEMPO_DE_ESPERA_FIJO 1 // Al menos espera esto

int arr[ARRLEN];

Locker locker;

void * escritor(void * arg) {
    int i;
    int num = arg - (void*)0;
    while (1) {
        sleep(random() % TIEMPO_DE_ESPERA + TIEMPO_DE_ESPERA_FIJO);

        locker_wait_privado(&locker);

        printf("Escritor %d escribiendo\n", num);
        for (i = 0; i < ARRLEN; i++)
            arr[i] = num;

        locker_post_privado(&locker);
    }
    return NULL;
}
void * lector(void * arg) {
    int v, i;
    int num = arg - (void*)0;
    int j = 0;
    while (1) {
        sleep(random() % TIEMPO_DE_ESPERA + TIEMPO_DE_ESPERA_FIJO);

        locker_wait_publico(&locker);

        v = arr[0];
        /*
        // Para verificar que podría entrar otro lector en medio.
        printf("Lector %d comenzo a leer %d\n", num, v);
        sleep(1);
        */
        for (i = 1; i < ARRLEN; i++) {
            if (arr[i] != v)
                break;
        }
        if (i < ARRLEN) {
            printf("Lector %d, error de lectura, %d ,%d\n", num, v, arr[i]);
            exit(EXIT_FAILURE);
        }
        else
            printf("Lector %d termino de leer dato %d\n", num, v);

        locker_post_publico(&locker);

    }
    return NULL;
}

/* 
// Luego de medio segundo, imprime cada medio segundo
void * test_function(void * arg) {
    usleep((int) (0.5 * (float) 1000000));
    while(1) {
        sleep(1);   
        printf("-----------------------------\n");
    }
}
*/

int main() {

    locker_init(&locker);

    pthread_t lectores[M], escritores[N];
    int i;
    for (i = 0; i < N; i++)
        pthread_create(&escritores[i], NULL, escritor, i + (void*)0);
    for (i = 0; i < M; i++)
        pthread_create(&lectores[i], NULL, lector, i + (void*)0);

    /*
    // Para imprimir alternadamente
    pthread_t test;
    pthread_create(&test, NULL, test_function, NULL);
    */

    pthread_join(lectores[0], NULL); /* Espera para siempre */

    return 0;
}