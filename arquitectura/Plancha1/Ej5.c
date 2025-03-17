#include<stdio.h>
#include<stdlib.h>

/**
 * Esta funcion recibe una clave y una cadena 
 * y la imprime codificada char a char usando xor.
 * @param clave Clave para usar el xor
 * @param cadena Cadena a codificar
 */
void codificar(int clave, char* cadena) {

    for (char* c = cadena; *c != '\0'; c++) {

        printf("%c", *c ^ clave);
    }

}

int main(int argc, char* argv[]) {

    codificar(atoi(argv[1]), argv[2]);  

    return 0;
}