#ifndef __BARRIER_H__
#define __BARRIER_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

struct barrier {
    int total;
    pthread_mutex_t mutexActuales;
    pthread_cond_t cond;
    int actuales;
};


void barrier_init(struct barrier *b, int n);

void barrier_wait(struct barrier *b);


#endif // __BARRIER_H__