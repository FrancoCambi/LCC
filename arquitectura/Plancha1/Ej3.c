#include<stdio.h>
#include<stdlib.h>

void printbin_recursive(long n) {

    if (n == 1) {
        printf("1");
    }
    else if (n == 0) {
        printf("0");
    }
    else {
        
        printbin_recursive(n / 2);
        
        if (n % 2 == 0) {
            printf("0");
        }
        else {
            printf("1");
        }

    }
}

/**
 * Imprime un entero sin signo de 32 bits en formato binario
 * @param n El número a imprimir en binario
 */
void printbin(unsigned long n) {
    // Un entero de 32 bits tiene 32 bits
    int bits = sizeof(unsigned long) * 8;
    
    // Recorrer cada bit, empezando por el más significativo
    for (int i = bits - 1; i >= 0; i--) {
        // Obtener el bit en la posición i
        int bit = (n >> i) & 1;
        
        // Imprimir el bit (0 o 1)
        printf("%d", bit);
        
        // Opcional: agregar un espacio cada 8 bits para mejorar la legibilidad
        if (i % 8 == 0 && i > 0) {
            printf(" ");
        }
    }
    
    printf("\n");
}

int main (int argc, char* argv[]) {


    printbin_recursive(strtol(argv[1], NULL, 10));

    printf("\n");

    printbin(strtol(argv[1], NULL, 10));

    return 0;
}