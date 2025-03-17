#include<stdio.h>
#include<stdlib.h>

int main(void) {


    int *var = malloc(100);

    free(var);

    free(var);
    return 0;
}