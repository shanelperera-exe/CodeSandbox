#include <stdio.h>

int main(void) {
    int num, sum;
    sum = 0;
    for(num = 2; num <=10; num++) {
        if (num % 2 == 0) {
            sum += num;
        }
    }
    printf("Sum of even numbers from 2 to 10: %d\n", sum);
    return 0;
}