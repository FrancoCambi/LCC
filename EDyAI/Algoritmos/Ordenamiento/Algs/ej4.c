#include<stdio.h>
#include<stdlib.h>

int *mezclar(int *arr1, int* arr2, int len1, int len2);
int *mergeSort(int *arr, int low, int high);

int main(void) {

    int arr[] = {5,6,7,8,9,1,5,7};
    int len = 8;

    int *arrResultado = mergeSort(arr, 0, len - 1);

    for (int i = 0; i < len; i++) 
        printf("%d ", arrResultado[i]);

    return 0;
}

int *mezclar(int *arr1, int* arr2, int len1, int len2) {

    int i = 0, j = 0, k = 0;

    // primer arreglo [low, ...., mid] -> len1
    // segundo arreglo [mid + 1, ....., high] -> len2

    int *arrResultado = malloc(sizeof(int) * (len1 + len2));

    // se unen hasta que uno de los dos arreglos
    // llegue al final.
    while (i < len1 && j < len2) {

        if (arr1[i] <= arr2[j]) {
            arrResultado[k] = arr1[i];
            i++;
        }
        else {
            arrResultado[k] = arr2[j];
            j++;
        }
        k++;
    }

    // Se agrega el resto del que no llego al final
    while (i < len1) {
        arrResultado[k] = arr1[i];
        i++;
        k++;
    }
    while (j < len2) {
        arrResultado[k] = arr2[j];
        j++;
        k++;
    }
    
    return arrResultado;
}

int *mergeSort(int *arr, int low, int high) {

    int len = high - low + 1;
    if (len == 1) return arr + low;

    int mid = (low + high) / 2;

    int* arr1 = mergeSort(arr, low, mid);
    int* arr2 = mergeSort(arr, mid + 1, high);

    int *arrResultado = mezclar(arr1, arr2, (mid - low + 1), (high - mid));

    for (int i = low; i <= high; ++i) {
        arr[i] = arrResultado[i - low];
    }

    free(arrResultado);

    return arr + low;
  
}