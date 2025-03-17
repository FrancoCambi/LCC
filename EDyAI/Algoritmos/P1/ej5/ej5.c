#include<stdio.h>
#include<stdlib.h>

int *sobrevivienteAux(int *arr, int longitud);
int sobreviviente(int n);

int main(void) {


    int n = 18;

    printf("%d", sobreviviente(n));

    return 0;
}

//O(n)
int *sobrevivienteAux(int *arr, int longitud) {
    
    int longitudActual = longitud;

    for (int i = 0, j = 0; longitud > 1; i += 2, j++) {
        if (i == longitud + 1) {
            i = 1;
            j = 0;
            longitud -= longitudActual;
            longitudActual = longitud;
        }
        else if (i == longitud) {
            i = 0;
            j = 0;
            longitud -= longitudActual;
            longitudActual = longitud;
        }
        arr[j] = arr[i];
        longitudActual--;

    }
            
    return arr;
}

//O(2n)
int sobreviviente(int n) {

    int *arr = malloc(sizeof(int) * n), resultado;
    for (int i = 1; i <= n; i++) 
        arr[i - 1] = i;
    
    resultado = sobrevivienteAux(arr, n)[0];
    free(arr);
    return resultado;
    
}