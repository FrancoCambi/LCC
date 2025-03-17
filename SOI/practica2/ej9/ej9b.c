#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N_VISITANTES 1000000
#define CANT_MOLINETES 2

int visitantes = 0;
int turn = 0;
int flag[2] = {0,0};

void *molinete1(void *arg) {
    for (int i = 0; i < N_VISITANTES/CANT_MOLINETES; i++) {
        
        flag[0] = 1;
        turn = 2;
        while(flag[1] && turn == 2);
        visitantes++;

        flag[0] = 0;
    }
}

void *molinete2(void *arg) {
    for (int i = 0; i < N_VISITANTES/CANT_MOLINETES; i++) {
        
        flag[1] = 1;
        turn = 1;
        while(flag[0] && turn == 1);
        visitantes++;

        flag[1] = 0;   
    }
}

int main() {
    
    pthread_t m1, m2;
    pthread_create(&m1, NULL, molinete1, NULL);
    pthread_create(&m2, NULL, molinete2, NULL);

    pthread_join(m1, NULL);
    pthread_join(m2, NULL);

    printf("VISITANTES: %d\n", visitantes);

    return 0;
}

/*
    real	0m0,060s
    user	0m0,120s
    sys	    0m0,000s
    VISITANTES: 1000000
*/