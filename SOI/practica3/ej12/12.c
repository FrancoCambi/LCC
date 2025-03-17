#include <pthread.h>

typedef struct _Semaphore {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int value;
} Semaphore;

int sem_init(Semaphore * sem, int pshared, unsigned int value) {
    pthread_cond_init(&sem->cond, NULL);
    pthread_mutex_init(&sem->mutex, NULL);
    sem->value = value;

    return 0; 
}

int sem_wait(Semaphore * sem) {
    pthread_mutex_lock(&sem->mutex);
    while(sem->value <= 0)
        pthread_cond_wait(&sem->cond, &sem->mutex);
    sem->value--;
    pthread_mutex_unlock(&sem->mutex);

    return 0;
}

int sem_post(Semaphore * sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value++;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mutex);

    return 0;
}

int sem_destroy(Semaphore * sem) {
    pthread_cond_destroy(&sem->cond);
    pthread_mutex_destroy(&sem->cond);

    return 0;
}

