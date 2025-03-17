#include<stdio.h>

unsigned int expMio(int b,  unsigned int n);

int main(void) {

    int b, n;
    printf("b y n: ");
    scanf("%d %d", &b, &n);
    printf("%d", expMio(b, n));

    return 0;
}


//O(n)
unsigned int expMio(int b,  unsigned int n) {

    int resultado = 1;
    for (int i = 0; i < n; i++) 
        resultado *= b;
    
    return resultado;
    
}