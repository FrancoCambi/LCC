/**
 * Esta variante funciona pero no es eficiente para nada. Depende de la velocidad 
 * en la que se realicen los procesos y depende de cuando tiempo espere el 
 * comensal antes de verificar si puede tomar el tenedor. Esto conlleva a que si
 * el tiempo de espera es demasiado corto, se produce un busywaiting, y si es 
 * demasiado largo entonces es ultra ineficiente ya que esta esperando cuando 
 * podria tomar el tenedor. Las otras formas son mas eficientes 
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define N_FILOSOFOS 5
#define ESPERA 1//5000000

pthread_mutex_t tenedor[N_FILOSOFOS];
pthread_mutex_t * izq(int i) { return &tenedor[i]; }
pthread_mutex_t * der(int i) { return &tenedor[(i+1) % N_FILOSOFOS]; }

void pensar(int i) {
    printf("Filosofo %d pensando...\n", i);
    usleep(random() % ESPERA);
}

void esperar(int i) {
    printf("Filosofo %d esperando...\n\n", i);
    usleep(random() % ESPERA);
}

void comer(int i) {
    printf("Filosofo %d comiendo...\n", i);
    usleep(random() % ESPERA);
}
void tomar_tenedores(int i) {
    pthread_mutex_lock(der(i));

    if(pthread_mutex_trylock(izq(i)) != 0) {
        pthread_mutex_unlock(der(i));
        esperar(i);
        tomar_tenedores(i);    
    }

}

void dejar_tenedores(int i) {
    pthread_mutex_unlock(der(i));
    pthread_mutex_unlock(izq(i));
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

/*
*/