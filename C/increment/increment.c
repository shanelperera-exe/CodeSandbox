#include <stdio.h>

int main(void) {
    float x = 5.5;
    float *p = &x;

    printf("Address before increment: %p\n", p);
    p++;

    printf("Address after increment: %p\n", p);    
    return 0;
}