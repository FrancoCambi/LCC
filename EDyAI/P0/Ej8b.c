#include<stdio.h>
#include<stdlib.h>


void apply_in(int (*)(int), int*);
int func(int);

int main(void) {

    int num;

    printf("Ingrese un numero: ");
    scanf("%d", &num);

    printf("Numero ingresado: %d\n", num);

    apply_in(func, &num);

    printf("Numero ahora: %d\n", num);

    return 0;
}

int func(int num) {

    printf("Haciendo algo con %d\n", num);

    return num - 1;
}

void apply_in(int (*func)(int), int *num) {

    *num = (*func)(*num);

}