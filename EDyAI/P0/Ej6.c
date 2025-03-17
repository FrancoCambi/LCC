#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define READSIZE 10
#define STR(s) STR2(s)
#define STR2(s) #s


char *get_new_line(void) {

    char buffer[READSIZE + 1], *linea = NULL, *ptr;
    int seguir = 1, long_total = 0, long_actual = 0;

    while (seguir) {
        fgets(buffer, READSIZE + 1, stdin);
        ptr = strchr(buffer, '\n');

        if (ptr != NULL) {
            *ptr = '\0';
            seguir = 0;
        }

        long_actual = strlen(buffer);
        linea = realloc(linea, sizeof(char) * (long_total + long_actual + 1));
        strcpy(linea + long_total, buffer);
        long_total += long_actual;
    }

    return linea;
}

int main(void) {


    printf("Ingrese una cadena: ");
    char *linea = get_new_line();
    printf("Cadena ingresada: %s\n", linea);
    free(linea);

    return 0;
}