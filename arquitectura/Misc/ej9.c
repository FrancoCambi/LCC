#include<stdio.h>
#include<ieee754.h>

int extr_exponente(float num);
unsigned int extr_fraccion(float num);

int main(void) {

    union ieee754_float a;
    float num = 2.5;

    a.f = num;

    unsigned int man = a.ieee.mantissa;
    
    printf("Exponente: -> %d | cabecera ieee754 -> %d\n", extr_exponente(num), a.ieee.exponent - 127);
    printf("Fraccion: -> %x | cabecera ieee754 -> %x\n", extr_fraccion(num), a.ieee.mantissa);

    return 0;
}

int extr_exponente(float num) {

    int value = *((int*) &num);
    return (value >> 23) - 127;
}

unsigned int extr_fraccion(float num) {

    int value = *((int*) &num);

    return (value & 0x007fffff);
}