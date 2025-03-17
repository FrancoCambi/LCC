#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define M 5
#define N 5
#define ARRLEN 10240

int arr[ARRLEN];

pthread_mutex_t mutexRC = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condRC = PTHREAD_COND_INITIALIZER;
int leyendo = 0;

void * escritor(void *arg) {
    int i;
    int num = arg - (void*)0;
    int j = 0;
    while (1) {
        //usleep(random() % 3);
        
        pthread_mutex_lock(&mutexRC);
        while (leyendo > 0) {
            pthread_cond_wait(&condRC, &mutexRC);
        }

        printf("Escritor %d escribiendo\n", num);
        for (i = 0; i < ARRLEN; i++)
            arr[i] = num;

        pthread_mutex_unlock(&mutexRC);
    }
    return NULL;
}
void * lector(void *arg) {
    int v, i;
    int num = arg - (void*)0;
    int j = 0;
    while (1) {
        //usleep(random() % 3);

        pthread_mutex_lock(&mutexRC);
        leyendo++;
        pthread_mutex_unlock(&mutexRC);

        v = arr[0];
        printf("Lector %d comenzo a leer %d - ", num, v);
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

        pthread_mutex_lock(&mutexRC);
        leyendo--;
        pthread_cond_signal(&condRC);
        pthread_mutex_unlock(&mutexRC);

    }
    return NULL;
}
int main() {
    pthread_t lectores[M], escritores[N];
    int i;
    for (i = 0; i < N; i++)
        pthread_create(&escritores[i], NULL, escritor, i + (void*)0);
    for (i = 0; i < M; i++)
        pthread_create(&lectores[i], NULL, lector, i + (void*)0);
    pthread_join(lectores[0], NULL); /* Espera para siempre */
    return 0;
}
