#include<stdio.h>

int string_len(char *str) {
    int i = 0;
    while (*str != '\0') {
        str++;
        i++;
    }
    return i;
}

int main(void) {

    printf("%d\n", string_len(""));

    return 0;
}