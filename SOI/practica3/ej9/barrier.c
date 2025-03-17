#include "barrier.h"

void barrier_init(struct barrier *b, int n) {
    pthread_cond_init(&b->cond, NULL);
    pthread_mutex_init(&b->mutexActuales, NULL);
    b->total = n;
    b->actuales = 0;
}   

void barrier_wait(struct barrier *b) {
    pthread_mutex_lock(&b->mutexActuales);
    b->actuales++;
    if (b->actuales == b->total) {
        b->actuales = 0;
        pthread_cond_broadcast(&b->cond);
    }
    else 
        pthread_cond_wait(&b->cond, &b->mutexActuales);
    pthread_mutex_unlock(&b->mutexActuales);
}