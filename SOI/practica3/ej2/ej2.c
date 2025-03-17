#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

pthread_mutex_t lk1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lk2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv2 = PTHREAD_COND_INITIALIZER;

int boolA1 = 0;
int boolB1 = 0;


void *funcion_A() {

    pthread_mutex_lock(&lk1);
    printf("a1\n");
    boolA1 = 1;
    pthread_cond_signal(&cv1);
    pthread_mutex_unlock(&lk1);
    
    pthread_mutex_lock(&lk2);
    while (!boolB1)
        pthread_cond_wait(&cv2, &lk2);
    printf("a2\n");
    pthread_mutex_unlock(&lk2);
}

void *funcion_B() {

    pthread_mutex_lock(&lk2);
    printf("b1\n");
    boolB1 = 1;
    pthread_cond_signal(&cv2);
    pthread_mutex_unlock(&lk2);

    pthread_mutex_lock(&lk1);
    while (!boolA1)
        pthread_cond_wait(&cv1, &lk1);
    printf("b2\n");
    pthread_mutex_unlock(&lk1);
}



int main() {
    
    pthread_t A, B;

    pthread_create(&A, NULL, funcion_A, NULL);
    pthread_create(&B, NULL, funcion_B, NULL);

    pthread_join(A, NULL);
    pthread_join(B, NULL);

    printf("------------------\n");

    return 0;
}