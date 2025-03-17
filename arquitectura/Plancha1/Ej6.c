#include<stdio.h>
#include<stdlib.h>

unsigned mult(unsigned a, unsigned b) {
    unsigned result = 0;
    
    while (b > 0) {
        // Si b es impar, sumamos a al resultado
        if (b & 1) {
            result += a;
        }
        
        // Duplicamos a y dividimos b por 2
        a = a << 1;  // Multiplicar a por 2 (desplazamiento a la izquierda)
        b = b >> 1;  // Dividir b por 2 (desplazamiento a la derecha)
    }
    
    return result;
}

int main(int argc, char* argv[]) {

    printf("%d", mult(atoi(argv[1]), atoi(argv[2])));  

    return 0;
}