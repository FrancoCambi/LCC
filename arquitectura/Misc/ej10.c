#include<stdio.h>
#include<ieee754.h>
#include<math.h>

int my_isnan(float num);

int main(void) {

    float g = 0.0;
    float f = 0.0 / g;

    printf("%d\n", my_isnan(f));

    return 0;
}

int my_isnan(float num) {

    int value = *((int*) &num);

    return ((value >> 23 & 0xff) == 0xff) &&
            ((value & 0x007fffff) != 0);
}