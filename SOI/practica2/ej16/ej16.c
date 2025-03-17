#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>

#define CANT_THREADS 10
#define N_VISITANTES 1000

int numero[CANT_THREADS] = {0};
int eligiendo[CANT_THREADS] = {0};

int visitantes = 0;

int max(int * arr, int len) {

    int max = arr[0];

    for (int i = 0; i < len; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

void lock(int threadId) {
    eligiendo[threadId] = 1;
    numero[threadId] = 1 + max(numero, CANT_THREADS);
    eligiendo[threadId] = 0;

    for (int j = 0; j < CANT_THREADS; j++) {
        while(eligiendo[j]);

        while(numero[j] != 0  && (numero[j] < numero[threadId] || (numero[j] == numero[threadId] && j < threadId)));
    }
}

void unlock(int threadId) {
    numero[threadId] = 0;
}

/* codigo del cada threadId*/
void *client_thread(void * threadIdPointer) {
    int threadId = *(int *)threadIdPointer;

    for(int i = 0; i < N_VISITANTES/CANT_THREADS; i++) {
        lock(threadId);

        visitantes++;

        unlock(threadId);
    }
}

int main() {
    pthread_t threads[CANT_THREADS];
    int threadIds[CANT_THREADS];

    for (int i = 0; i < CANT_THREADS; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, client_thread, (void *)&threadIds[i]);
    }

    for (int i = 0; i < CANT_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nSe calcularn %d visitantes.\n", visitantes);

    return 0;
}
