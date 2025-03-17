#include<stdio.h>
#include<stdlib.h>

int solve(float a, float b, float c, float d, float e, float f, float *x, float *y);

int main(){
    float a = 2;
    float b = 2;
    float c = 10;
    float d = 3;
    float e = 4;
    float f = 15;
    float *x = malloc(sizeof(float));
    float *y = malloc(sizeof(float));
    printf("El resultado es: %d\n", solve(a,b,c,d,e,f,x,y));
    printf("x = %f\ny = %f\n", *x, *y);
    return 0;
}