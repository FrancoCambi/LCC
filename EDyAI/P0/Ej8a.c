#include<stdio.h>
#include<stdlib.h>


int apply(int (*)(int), int);
int func(int);

int main(void) {

    int num;

    printf("Ingrese un numero: ");
    scanf("%d", &num);

    printf("Numero ingresado: %d\n", num);

    int new_num = apply((*func), num);

    printf("New num: %d\n", new_num);

    return 0;
}

int func(int num) {

    printf("Haciendo algo con %d\n", num);

    return num - 1;
}

int apply(int (*func)(int), int num) {

    int new_num;

    new_num = (*func)(num);

    return new_num;

}