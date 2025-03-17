#include<stdio.h>
#include<stdlib.h>

int fibonacciAux(int n, int* calculado, int* memo);
int fibonacci(int n);
int fibonacciFor(int n);


int main(void) {

    int num, result;
    printf("Numero para calcular el fib: ");
    scanf("%d", &num);

    result = fibonacci(num);
    printf("%d", result);

    return 0;
}

int fibonacciAux(int n, int* calculado, int* memo) {

    if (calculado[n]) 
        return memo[n];

    if (n == 0)
        return 0;
    
    if (n == 1)
        return 1;

    int resultado = fibonacciAux(n - 1, calculado, memo) + fibonacciAux(n - 2, calculado, memo);

    calculado[n] = 1;
    memo[n] = resultado;

    return resultado;
    
}

//O(n*2);
int fibonacci(int n) {

    int* memo = malloc(sizeof(int) * (n + 1));
    int* calculado = calloc(n + 1, sizeof(int));
    int resultado = fibonacciAux(n, calculado, memo);
    free(memo);
    free(calculado);
    return resultado;
}


// O(n)
int fibonacciFor(int n){
    int* memo = malloc(sizeof(int) * (n + 1));
    int resultado;
    memo[0] = 0;
    memo[1] = 1;

    for (int i = 2; i <= n; i++){

        memo[i] = memo[i - 1] + memo[i - 2];
    }

    resultado = memo[n];
    free(memo);
    return resultado;

}