/**
 * 1 2 3 4 5 6 7 8 9 10
 * 2 3 5 6 4 
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <semaphore.h>
#include <pthread.h>
#include "barrier.h"

#define ITERS 1000
#define N 10
#define W 5

struct barrier barrier;

float arr1[N], arr2[N];
void calor(float *arr, int lo, int hi, float *arr2) {
    int i;
    for (i = lo; i < hi; i++) {
        int m = arr[i];
        int l = i > 0 ? arr[i-1] : m;
        int r = i < N-1 ? arr[i+1] : m;
        arr2[i] = m + (l - m)/1000.0 + (r - m)/1000.0;
    }
}

int min(int i, int j) {
    return i < j ? i : j;
}
/* Dado un array de [n], devuelve el punto de corte [i] de los [m] totales. */
static inline int cut(int n, int i, int m) {
    return i * (n / m) + min(i, n % m);
}
void * thr(void *arg) {
    int id = arg - (void*)0; /* 0 <= id < W */
    int lo = cut(N, id, W), hi = cut(N, id+1, W);
    int i;
    for (i = 0; i < ITERS; i++) {
        calor(arr1, lo, hi, arr2);
        calor(arr2, lo, hi, arr1);
        barrier_wait(&barrier);
    }
}

int main() {

    barrier_init(&barrier, W);

    
    printf("ARR1: ");
    for (int i = 0; i < N; i++) {
        arr1[i] = (float) (random() % 15);
        printf("%.2f - ", arr1[i]);
    }
    printf("\nARR2: ");
    for (int i = 0; i < N; i++) {
        arr2[i] = (float) (random() % 15);
        printf("%.2f - ", arr2[i]);
    }
    puts("");
    
    pthread_t threads[W];
    for (int i = 0; i < W; i++){
        pthread_create(&threads[i], NULL, thr, i + (void *)0);
    }
    for (int i = 0; i < W; i++){
        pthread_join(threads[i], NULL);
    }
    printf("ARR1: ");
    for (int i = 0; i < N; i++) {
        printf("%.2f - ", arr1[i]);
    }
    printf("\nARR2: ");
    for (int i = 0; i < N; i++) {
        printf("%.2f - ", arr2[i]);
    }
    puts("");
    
    return 0;
}
