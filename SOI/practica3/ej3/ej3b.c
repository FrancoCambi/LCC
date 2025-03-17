/*
b) Ya que nunca se a va producir un caso en el que el comensal zurdo y el comensal derecho 
yuxtapuesto quieran agarrar el segundo tenedor
sin tener ya en sus manos el primero, por lo que alguno de los dos eventualmente 
va a agarrar el tenedor y siempre
alguien va a poder comer, lo que libera el deadlock que se podria producir antes.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define ID_COMENSAL_ZURDO 0
#define N_FILOSOFOS 5
#define ESPERA 5 //5000000

pthread_mutex_t tenedor[N_FILOSOFOS];
pthread_mutex_t * izq(int i) { return &tenedor[i]; }
pthread_mutex_t * der(int i) { return &tenedor[(i+1) % N_FILOSOFOS]; }

void pensar(int i) {
    printf("Filosofo %d pensando...\n", i);
    usleep(random() % ESPERA);
}
void comer(int i) {
    printf("Filosofo %d comiendo...\n", i);
    usleep(random() % ESPERA);
}
void tomar_tenedores(int i) {
    if(i == ID_COMENSAL_ZURDO) {
        pthread_mutex_lock(izq(i));
        pthread_mutex_lock(der(i));
    }
    else {
        pthread_mutex_lock(der(i));
        pthread_mutex_lock(izq(i));
    }
}

void dejar_tenedores(int i) {
    if(i == ID_COMENSAL_ZURDO) {
        pthread_mutex_unlock(izq(i));
        pthread_mutex_unlock(der(i));
    }
    else {
        pthread_mutex_unlock(der(i));
        pthread_mutex_unlock(izq(i));
    }
}
void * filosofo(void *arg) {
    int i = arg - (void*)0;
    for (int j = 0; j < 100; j++) {
        tomar_tenedores(i);
        comer(i);
        dejar_tenedores(i);
        pensar(i);
    }
}
int main() {
    pthread_t filo[N_FILOSOFOS];
    int i;
    for (i = 0; i < N_FILOSOFOS; i++)
        pthread_mutex_init(&tenedor[i], NULL);
    for (i = 0; i < N_FILOSOFOS; i++)
        pthread_create(&filo[i], NULL, filosofo, i + (void*)0);
    pthread_join(filo[0], NULL);
    return 0;
}