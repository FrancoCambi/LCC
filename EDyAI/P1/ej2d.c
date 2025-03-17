#include<stdio.h>
#include<string.h>

int string_compare(char *str1, char *str2) {

    // 0 default para strings iguales
    int resultado = 0;
    
    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
        str1++;
        str2++;
    }

    if (*str1 > *str2)
        resultado = 1;
    else if (*str1 < *str2)
        resultado = -1;


    return resultado;

}


int main() {

    printf("%d\n", string_compare("abc", "abc"));
    return 0;
}