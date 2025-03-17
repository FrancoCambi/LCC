#include<stdio.h>

int is_one(long n, int b) {

    return (n >> b) & 1;
    //return ((1 << b) | n) == n;
}

int main (void) {


    printf("%d", is_one(0b1010, 3));

    return 0;
}