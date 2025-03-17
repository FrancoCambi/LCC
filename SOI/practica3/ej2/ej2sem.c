#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

sem_t semA1B2, semA2B1;

void *funcion_A() {

    printf("a1 -\n");
    sem_post(&semA1B2);

    sem_wait(&semA2B1);
    printf("a2\n");
}

void *funcion_B() {

    printf("b1 -\n");
    sem_post(&semA2B1);    
    
    sem_wait(&semA1B2);
    printf("b2\n");
}

int main() {
    
    sem_init(&semA1B2, 0, 0);
    sem_init(&semA1B2, 0, 0);

    pthread_t A, B;

    pthread_create(&A, NULL, funcion_A, NULL);
    pthread_create(&B, NULL, funcion_B, NULL);

    pthread_join(A, NULL);
    pthread_join(B, NULL);

    printf("------------------\n");

    return 0;
}