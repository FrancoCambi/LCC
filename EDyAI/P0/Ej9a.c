#include<stdio.h>

int main () {
    int* punt ;
    int x = 7 , y = 5;
    punt = &x ;
    *punt = 4;
    printf("%d %d", x, y);

    return 0;
}