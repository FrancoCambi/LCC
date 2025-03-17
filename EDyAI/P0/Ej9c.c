#include<stdio.h>

int main(void) {

    int* punt, i;
    int x[] = {1,2,3,4,5};
    punt = x;
    *punt = 9;
    for (i = 0; i < 5; i++)
        printf("%d, ", x[i]);

    return 0;
}