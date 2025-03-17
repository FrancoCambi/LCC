#include<stdio.h>
#include<math.h>

void bubble_sort(float arr[], int longitud);
float mediana(float *arr, int longitud);

int main(void) {

    float arr[6] = {10,15,18,5,1,2}; // 1 2 5 10 15 18
    printf("%f", mediana(arr, 6));

    return 0;
}

float mediana(float *arr, int longitud) {

    float copia[longitud], resultado;

    for (int i = 0; i < longitud; i++)
        copia[i] = arr[i];
    
    bubble_sort(copia, longitud);

    if (longitud % 2 != 0) 
        resultado = copia[longitud/2];
    else {
        int index_1 = round((longitud - 1) / 2);
        int index_2 = round((longitud - 1) / 2) + 1;
        float medio_1 = copia[index_1];
        float medio_2 = copia[index_2];

        resultado = (medio_1 + medio_2) / 2;

    }

    return resultado;
        
}

void bubble_sort(float arr[], int longitud) {

    for (int iter = 0; iter < longitud -1; iter++) {
        for (int i = 0; i < longitud - iter - 1; i++) {
            if (arr[i] > arr[i + 1]){
                float aux = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = aux;
            }

        }
    }

}