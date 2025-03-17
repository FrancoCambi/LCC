#include<stdio.h>
/**
 * @brief Cambia un valor pasado a 1 si no era 0
 * 
 * @param int 
 */
void set_int(int *num);

int main(void) {

    int num = 5;

    printf("Antes: %d\n", num);

    set_int(&num);

    printf("Despues: %d", num);

    return 0;
}

void set_int(int *num) {


    if (*num != 0)
      *num = 0;
}