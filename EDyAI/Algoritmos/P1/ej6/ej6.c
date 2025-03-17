#include<stdio.h>

size_t encontrarPico(int* arr, size_t longitud);
size_t encontrarPicoBinary(int* arr, size_t longitud);
size_t encontrarPicoBinaryAux(int* arr, size_t leftBorder, size_t rightBorder, size_t longitud);

int main(void) {

    int arr[] = {1,15,3,4,8};

    printf("%d", encontrarPicoBinary(arr, 5));

    return 0;
}

//O(n)
size_t encontrarPico(int *arr, size_t longitud) {

    if (arr[0] >= arr[1]) return 0;
    if (arr[longitud - 1] >= arr[longitud - 2]) return longitud - 1;

    for (int i = 1; i < longitud - 1; i++) {
        if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1])
            return i;
        
    }
}

//O(log n)
size_t encontrarPicoBinaryAux(int* arr, size_t leftBorder, size_t rightBorder, size_t longitud) {

    size_t mid = leftBorder + (rightBorder - leftBorder) / 2;

    if ((mid == 0 || arr[mid - 1] <= arr[mid]) && (mid == longitud - 1 || arr[mid + 1] <= arr[mid]))
        return mid;
    
    else if (mid > 0 && arr[mid - 1] > arr[mid])
        return encontrarPicoBinaryAux(arr, leftBorder, mid - 1, longitud);
    
    else 
        return encontrarPicoBinaryAux(arr, mid + 1, rightBorder, longitud);
}

size_t encontrarPicoBinary(int* arr, size_t longitud) {

    return encontrarPicoBinaryAux(arr, 0, longitud - 1, longitud);
}