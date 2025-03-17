#include<stdio.h>

int main(void) {

    int a = 3;
    char b = 'b';

    printf("Direccion de a: %p\nDireccion de b: %p", &a, &b);

    return 0;
}