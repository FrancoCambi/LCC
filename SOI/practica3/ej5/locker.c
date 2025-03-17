#include "locker.h"

void locker_init(Locker * locker) {
    locker->publicos = 0; // Hay 0 usuarios publicos al iniciar
    pthread_mutex_init(&locker->mutexRC, NULL);
    pthread_mutex_init(&locker->mutexPublicos, NULL);
    pthread_cond_init(&locker->cond, NULL);
    sem_init(&locker->ordenDeLlegada, 0, 1); // El primero puede simplemente entrar
}

void locker_wait_publico(Locker * locker) {
    sem_wait(&locker->ordenDeLlegada); // Es el primero de la fila, entra

    pthread_mutex_lock(&locker->mutexPublicos);
    locker->publicos++; // Avisa que es un publico que ingresa a la RC
    pthread_mutex_unlock(&locker->mutexPublicos);
    
    sem_post(&locker->ordenDeLlegada); // Le permite al siguiente usuario ingresar
}

void locker_post_publico(Locker * locker) {
    pthread_mutex_lock(&locker->mutexPublicos);
    locker->publicos--; // Avisa que deja la RC
    pthread_cond_signal(&locker->cond); // Avisa a algun posible privado que dejó la RC
    pthread_mutex_unlock(&locker->mutexPublicos);
}

void locker_wait_privado(Locker * locker) {
    sem_wait(&locker->ordenDeLlegada);  // Es el primero de la fila, entra
    pthread_mutex_lock(&locker->mutexPublicos);
    while (locker->publicos > 0) // Se fija si hay alguien publico en la RC, hasta que no haya
        pthread_cond_wait(&locker->cond, &locker->mutexPublicos); // En ese caso espera que le avise que se fue
    pthread_mutex_lock(&locker->mutexRC); // Entra a la RC
    pthread_mutex_unlock(&locker->mutexPublicos);
}

void locker_post_privado(Locker * locker) {
    pthread_mutex_unlock(&locker->mutexRC); // Deja la RC
    sem_post(&locker->ordenDeLlegada); // Le permite al siguiente usuario ingresar
}