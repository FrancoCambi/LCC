#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

void bubble_sort(float arreglo[], int longitud);

int main(void) {
    
    int longitud;
    float mediana;
    scanf("%d", &longitud);
    float *arr = malloc(sizeof(int) * longitud);
    for (int i = 0; i < longitud; i++) {
        float dato;
        scanf("%f", &dato);
        arr[i] = dato;
    }

    bubble_sort(arr, longitud);

    if (longitud % 2 == 0) {
        mediana = arr[longitud / 2 - 1] + arr[longitud / 2];
        mediana /= 2;
    }
    else {
        mediana = arr[longitud / 2];
    }

    printf("%f", mediana);

    return 0;
}

void bubble_sort(float arreglo[], int longitud) {
    for (int iter = 0; iter < longitud - 1; iter++) {
        for (int i = 0; i < longitud - iter - 1; i++) {
            if (arreglo[i] > arreglo[i + 1]) {
                float aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
            }
        }
    }
}