#include<stdio.h>
/**
 * @brief Setea el primer elemento de un array a 0
 * 
 * @param int arr[] 
 */
void set_first(int arr[]);

int main(void) {

    int arr[8] = {1,2,3,4,5,6,7,8};

    set_first(arr);

    return 0;
}

void set_first(int arr[]) {

    printf("Antes: %d\n", arr[0]);

    arr[0] = 0;

    printf("Luego: %d", arr[0]);
}