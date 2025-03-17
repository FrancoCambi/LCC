#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

/**
 * Implementacion de un locker, que funciona para administrar el ingreso a una 
 * RC de manera ordenada a aquellos threads que lo deseen. Aquellos threads o
 * usuarios que no tengan inconvenientes en entrar acompañados a la RC se 
 * entienden como PUBLICOS y aquellos que deban entrar solos se entienden como 
 * PRIVADOS. Cada uno pedirá la funcion que le corresponda.
*/

#include <semaphore.h>
#include <pthread.h>

/**
 * Tipo de dato que administra la organizacion. */
typedef struct _Locker {
    /**
     * Funciona como semaforo de true/false, y sirve para registrar el orden de 
     * llegada y permitir entrar a quien haya llegado primero. Comienza por 1 
     * (true) */
    sem_t ordenDeLlegada;

    /**
     * Es el mutex de la region critica. Solo lo van a necesitar los usuarios 
     * privados. */
    pthread_mutex_t mutexRC;
    
    /**
     * Es el condicional que sirve para que los públicos le comuniquen a un posible 
     * privado que ya terminaron de usar la RC. */
    pthread_cond_t cond;
    
    /**
     * Es el mutex del contador de publicos. */
    pthread_mutex_t mutexPublicos;

    /**
	     * Es la variable que indica cuantos publicos estan usando la region critica. 
     * Comienza en 0, y cada vez que un publico entra suma, y cuando se va resta. */
    int publicos;
} Locker;

/**
 * Inicializa los valores del locker. */
void locker_init(Locker * locker);

/**
 * Aquellos publicos que quieran ingresar a la RC deben pedir este "wait" o "lock" */
void locker_wait_publico(Locker * locker);

/**
 * Aquellos publicos que hayan dejado la RC deben enviar este "post" o "unlock" */
void locker_post_publico(Locker * locker);

/**
 * Aquellos privados que quieran ingresar a la RC deben pedir este "wait" o "lock" */
void locker_wait_privado(Locker * locker);

/**
 * Aquellos privados que hayan dejado la RC deben enviar este "post" o "unlock" */
void locker_post_privado(Locker * locker);

#endif // __INTERFAZ_H__
