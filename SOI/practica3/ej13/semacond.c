#include "semacond.h"

void cond_init(Cond * cond) {
    sem_init(&cond->sem1, 0, 0);
    sem_init(&cond->sem2, 0, 0);
    sem_init(&cond->m, 0, 1); // mutex
}

void cond_wait(Cond * cond, pthread_mutex_t * mutex) {
    sem_wait(&cond->m);
    cond->queue++;
    sem_post(&cond->m);

    pthread_mutex_unlock(&mutex);

    sem_post(&cond->sem2);
    sem_wait(&cond->sem1);

    pthread_mutex_lock(&mutex);
}

void cond_signal(Cond * cond) {
    sem_wait(&cond->m);
    if(cond->queue > 0) {
        cond->queue--;
        sem_post(&cond->sem1);
        sem_wait(&cond->sem2);
    }
    sem_post(&cond->m);
}

void cond_broadcast(Cond * cond) {
    sem_wait(&cond->m);
    for (int i = 0; i < cond->queue; i++)
        sem_post(&cond->sem1);
    while(cond->queue > 0) {
        cond->queue--;
        sem_wait(&cond->sem2);
    }

    sem_post(&cond->m);
}

void cond_destroy(Cond * cond) {
    sem_destroy(&cond->sem1);
    sem_destroy(&cond->sem2);
    sem_destroy(&cond->m);
}