#include<stdio.h>
#include<string.h>


int string_concat(char *str1, char *str2, int max) {

    int longitud_str1 = strlen(str1);
    int i;

    for (i = 0; i < max; i++) {

        str1[longitud_str1 + i] = str2[i];
    }

    str1[longitud_str1 + i + 1] = '\0';

    return i;

}

int main(void) {

    char str1[10] = "hola";
    char str2[] = "jaja";

    string_concat(str1, str2, 4);

    printf("%s", str1);


    return 0;
}