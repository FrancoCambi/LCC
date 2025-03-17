#include<semaphore.h>
#include <pthread.h>

typedef struct _Cond {
    /* sem1 es el wait del wait y sem2 el del signal y broadcast para 
     * coordinar q no se meta nadie en medio */
    sem_t sem1, sem2;
    sem_t m; // mutex de queue
    int queue; // Cantidad de cond_wait en cola
} Cond;

void cond_init(Cond * cond);

void cond_wait(Cond * cond, pthread_mutex_t * mutex);

void cond_signal(Cond * cond);

void cond_broadcast(Cond * cond);

void cond_destroy(Cond * cond);