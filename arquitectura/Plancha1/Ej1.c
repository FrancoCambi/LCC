#include<stdio.h>

int main(void) {


    int numa = 1 << 31;
    int numb = (1 << 31) | (1 << 15);
    int numc = -1 & 0xFFFFFF00;
    int numd =  0xAA | (0xAA << 24);
    int nume = 5 << 8;
    int numf = -1 ^ (1 << 8);
    int numg = 0 - 1;
    int numh = 0x80000000 + 0x80000000;

    return 0;
}