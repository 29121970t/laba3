#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/parseLib4.h"
#include <limits.h>


typedef struct field {
    unsigned char _4 : 1;
    unsigned char _3 : 1;
    unsigned char _2 : 1;
    unsigned char _1 : 1;
    char : 4;

} field;
int isChar(char num){
    return num >= -128 && num <= 127;
}

int main(int argc, char const *argv[]) {
    char num;
    readCharWithDialog_v(&num, "Please enter a number (-128 >= n <= 127): ", NULL);
    field * fptr = (field *) &num;
    printf("Bits: %u%u%u%u\n", fptr->_1, fptr->_2, fptr->_3, fptr->_4);

    return 0;
}
