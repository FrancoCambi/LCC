#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t tabaco, papel, fosforos, otra_vez;
sem_t fumadorFosforos, fumadorPapel, fumadorTabaco;

void agente() {

    while (1) {
        sem_wait(&otra_vez);
        int caso = random() % 3;
        if (caso != 0) sem_post(&fosforos);
        else sem_post(&fumadorFosforos);
        if (caso != 1) sem_post(&papel);
        else sem_post(&fumadorPapel);
        if (caso != 2) sem_post(&tabaco);
        else sem_post(&fumadorTabaco);
    }
}
void fumar(int fumador) {

    printf("Fumador %d: Puf! Puf! Puf!\n", fumador);
    //sleep(1);
}
void * fumador1(void *arg) {

    while (1) {
        sem_wait(&fumadorFosforos);
        sem_wait(&tabaco);
        sem_wait(&papel);
        fumar(1);
        sem_post(&otra_vez);
    }
}
void * fumador2(void *arg) {

    while (1) {
        sem_wait(&fumadorPapel);
        sem_wait(&fosforos);
        sem_wait(&tabaco);
        fumar(2);
        sem_post(&otra_vez);
    }
}

void * fumador3(void *arg) {

    while (1) {
        sem_wait(&fumadorTabaco);
        sem_wait(&papel);
        sem_wait(&fosforos);
        fumar(3);
        sem_post(&otra_vez);
    }
}
int main() {

    pthread_t s1, s2, s3;
    sem_init(&tabaco, 0, 0);
    sem_init(&papel, 0, 0);
    sem_init(&fosforos, 0, 0);
    sem_init(&otra_vez, 0, 1);

    sem_init(&fumadorTabaco, 0, 0);
    sem_init(&fumadorPapel, 0, 0);
    sem_init(&fumadorFosforos, 0, 0);

    pthread_create(&s1, NULL, fumador1, NULL);
    pthread_create(&s2, NULL, fumador2, NULL);
    pthread_create(&s3, NULL, fumador3, NULL);
    agente();
    return 0;
}