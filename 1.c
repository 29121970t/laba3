#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct field {
    unsigned char _4 : 1;
    unsigned char _3 : 1;
    unsigned char _2 : 1;
    unsigned char _1 : 1;
    char _junk : 4;
} field;

int main(int argc, char const *argv[]) {
    
    char a = 2;
    struct field * num = &a;
    printf("%u", num->_1);
    printf("%u", num->_2);
    printf("%u", num->_3);
    printf("%u", num->_4);

    return 0;
}
