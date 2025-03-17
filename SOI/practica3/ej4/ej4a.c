#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5
#define N 5
#define SZ 8

typedef struct _Cola {

    int *arr[SZ];
    int primero;
    int ultimo;
}Cola;


/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */

Cola c;
sem_t lugares;
sem_t ocupados;
sem_t mutex; // mutex de c

void push(Cola *cola, int* p) {

    cola->arr[cola->ultimo] = p;

    cola->ultimo = (cola->ultimo + 1) % SZ;

}

int *pop(Cola *cola) {

    int *p = cola->arr[cola->primero];

    cola->primero = (cola->primero + 1) % SZ;

    return p;
}


void enviar(int *p) {
    
	sem_wait(&lugares);
    sem_wait(&mutex);
    push(&c, p);
    sem_post(&mutex);
    sem_post(&ocupados);
	return;
}

int * recibir() {

	sem_wait(&ocupados);
    sem_wait(&mutex);
    int *p = pop(&c);
    sem_post(&mutex);
    sem_post(&lugares);
	return p;
}

void * prod_f(void *arg) {
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

		int *p = malloc(sizeof *p);
		*p = random() % 100;
		printf("Productor %d: produje %p->%d\n", id, p, *p);
		enviar(p);
	}
	return NULL;
}

void * cons_f(void *arg) {
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

		int *p = recibir();
		printf("Consumidor %d: obtuve %p->%d\n", id, p, *p);
		free(p);
	}
	return NULL;
}

int main()
{

    c.primero = 0;
    c.ultimo = 0;

    sem_init(&ocupados, 0, 0);
    sem_init(&lugares, 0, SZ);
    sem_init(&mutex, 0, 1);
    
	pthread_t productores[M], consumidores[N];
	int i;

	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

	pthread_join(productores[0], NULL); /* Espera para siempre */
	return 0;
}
