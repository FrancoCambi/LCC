#include <stdio.h>
unsigned long fact(unsigned long);


int main(void)
{
    unsigned long x;
    scanf("%lu", &x);
    printf("fact2: %lu\n", fact(x));
    return 0;
}