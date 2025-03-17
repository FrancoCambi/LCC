#include <stdio.h>

/**
 * Rota los valores de tres variables sin usar variables auxiliares
 * a -> b, b -> c, c -> a
 * Utiliza las propiedades del operador XOR
 * @param a Dir del primer numero a rotar
 * @param b Dir del segundo numero a rotar
 * @param c Dir del tercer numero a rotar
 */
void rotar(int *a, int *b, int *c) {
    // Aplicamos una serie de operaciones XOR para rotar los valores
    *a = *a ^ *b ^ *c;  // a = a ^ b ^ c
    *b = *a ^ *b ^ *c;  // b = (a ^ b ^ c) ^ b ^ c = a
    *c = *a ^ *b ^ *c;  // c = (a ^ b ^ c) ^ a ^ c = b
    *a = *a ^ *b ^ *c;  // a = (a ^ b ^ c) ^ a ^ b = c
}


int main() {
    int a = 5, b = 10, c = 15;
    
    printf("Antes de rotar: a = %d, b = %d, c = %d\n", a, b, c);
    
    rotar(&a, &b, &c);
    
    printf("Después de rotar: a = %d, b = %d, c = %d\n", a, b, c);
    
    return 0;
}