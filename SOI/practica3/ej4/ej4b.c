#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5
#define N 5
#define SZ 8

typedef struct _Cola {

    int *arr[SZ + 1];
    int primero;
    int ultimo;
}Cola;


/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */

Cola c;
pthread_cond_t nonFullCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t nonEmptyCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void push(Cola *c, int* p) {

    c->arr[c->ultimo] = p;

    c->ultimo = (c->ultimo + 1) % (SZ + 1);

}

int *pop(Cola *c) {

    int *p = c->arr[c->primero];

    c->primero = (c->primero + 1) % (SZ + 1);

    return p;
}

int is_empty(Cola c) {
    return c.primero == c.ultimo;
}

int is_full(Cola c) {
    return c.primero == (c.ultimo + 1) % (SZ + 1);
}

void enviar(int *p)
{
    pthread_mutex_lock(&mutex);
	while(is_full(c))
        pthread_cond_wait(&nonFullCond, &mutex);
    push(&c, p);
    pthread_cond_signal(&nonEmptyCond);
    pthread_mutex_unlock(&mutex);
	return;
}

int * recibir()
{
    pthread_mutex_lock(&mutex);
	while(is_empty(c))
        pthread_cond_wait(&nonEmptyCond, &mutex);
    int *p = pop(&c);
    pthread_cond_signal(&nonFullCond);
    pthread_mutex_unlock(&mutex);
	return p;
}

void * prod_f(void *arg)
{
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

void * cons_f(void *arg)
{
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

	pthread_t productores[M], consumidores[N];
	int i;

	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

	pthread_join(productores[0], NULL); /* Espera para siempre */
	return 0;
}
