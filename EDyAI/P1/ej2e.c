#include<stdio.h>
#include<string.h>

int string_subcadena(char *str1, char *str2) {

    int longitud_str1 = strlen(str1);
    int longitud_str2 = strlen(str2);
    int i;

    for (i = 0; i < longitud_str1; i++) {
        for (int j = 0, flag = 1; j <= longitud_str2 && flag == 1; j++) {
            if (str1[i + j] != str2[j])
                flag = 0;
            else if (str2[j] == '\0')
                return i;

            
        }

    }

    return -1;
}


int main(void) {

    printf("%d\n", string_subcadena("batatas", "atas"));

    return 0;
}