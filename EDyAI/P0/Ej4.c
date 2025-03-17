#include<stdio.h>

/**
 * @brief Intercambia dos valores.
 * 
 * @param int*
 * @param int*
 */
void swap(int *a, int *b);

int main(void) {

    int a = 5;
    int b = 10;

    printf("Antes: a = %d y b = %d\n", a, b);

    swap(&a, &b);

    printf("Despues: a = %d y b = %d", a, b);

    return 0;
}

void swap(int *a, int *b) {

    int c = *b;

    *b = *a;
    *a = c;
}