#include<stdio.h>
#include<string.h>

void string_reverse(char *str) {

    int longitud = strlen(str);
    int i;

    /*
    for (i = 0; i < longitud / 2; i++) {
        for (int j = longitud - 1; j >= longitud / 2; j--) {
            char buffer = str[i];
            //printf("%c\n", buffer);
            str[i] = str[j];
            str[j] = buffer;
            printf("%s\n", str);
        }
    }
    */

   char temp;

   for (int i = 0, j = longitud - 1; i < longitud / 2; i++, j--) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
   }


}


int main(void) {

    char arr[] = "abcde";

    string_reverse(arr);

    printf("%s\n", arr);

    return 0;
}