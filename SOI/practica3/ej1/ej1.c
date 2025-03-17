/*
¿Es esto correcto? ¿Qu´e problema puede haber?
Es correcto en la semantica MESA ya que el thread no liberia el lk en el mismo momento
que envia la señal. Si bien podria ser una desventaja en otra ocación (ya que las variables M y P 
podrian ser alteradas por otro proceso LUEGO de que libere el lock (se meta en el medio de ambos procesos)), 
aca resulta una ventaja ya que nosotros 
decidimos cuando devolver el lock. Por lo tanto, no importa como se ordenen las 3 instrucciones dentro de la RC
siempre y cuando esten entre locks.
Si fuese sematica HOARE, el signal devolveria inmediatamente el lock al wait, resultando en un 
error en el codigo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

unsigned int P = 0; // pan
unsigned int M = 0; // manteca

void *funcion_A() {

    pthread_mutex_lock(&lk);
    if(!(P && M)) {
        pthread_cond_wait(&cv, &lk);
    }
    /*
    // Em una implementacion real deberia usarse while aún cuando no deberia 
    // jamas dar falso luego de que se libere el cv. Pero lo estariamos despertando "varias veces"
    while(!(P && M)) {
        pthread_cond_wait(&cv, &lk);
    }
    
    */


    if(!P || !M) // no pasa nunca porque B libera el lk luego de setear ambos a 1;
        exit(EXIT_FAILURE);
    else
        printf("Piola\n");
    pthread_mutex_unlock(&lk);
}

/**
 * Es correcto siempre y cuando A este bien diseñada. Seria mas lógico asignar M 
 * antes de enviar la señal.
*/
void *funcion_B() {
    pthread_mutex_lock(&lk);
    P = 1;
    pthread_cond_signal(&cv);
    M = 1;
    pthread_mutex_unlock(&lk);
}

int main() {
    
    pthread_t A, B;

    pthread_create(&B, NULL, funcion_B, NULL);
    pthread_create(&A, NULL, funcion_A, NULL);
    
    //sleep(1);

    pthread_join(A, NULL);
    pthread_join(B, NULL);

    return 0;
}