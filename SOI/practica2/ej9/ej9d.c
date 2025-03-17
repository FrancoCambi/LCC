#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N_VISITANTES 1000000
#define CANT_MOLINETES 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int visitantes = 0;

void *molinete(void *arg) {
    for (int i = 0; i < N_VISITANTES/CANT_MOLINETES; i++) {
        pthread_mutex_lock(&mutex);
        visitantes++;
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    
    pthread_t m1, m2;
    pthread_create(&m1, NULL, molinete, NULL);
    pthread_create(&m2, NULL, molinete, NULL);

    pthread_join(m1, NULL);
    pthread_join(m2, NULL);

    printf("VISITANTES: %d\n", visitantes);

    return 0;
}

/*
    real	0m0,042s
    user	0m0,055s
    sys	    0m0,027s
    VISITANTES: 1000000
*/