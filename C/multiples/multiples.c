#include <stdio.h>

int main(void) {
    for(int num = 1; num <= 5; num++) {
        int multiples = num * 4;
        printf("%d\n", multiples);
    }
    return 0;
}