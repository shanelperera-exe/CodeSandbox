#include <stdio.h>

int sum_recursive(int n);

int main(void) {
    int integer, sum_of_digits;

    printf("Enter an integer: ");
    scanf("%d", &integer);

    sum_of_digits = sum_recursive(integer);

    printf("Sum of digits: %d\n", sum_of_digits);

    return 0;
}

int sum_recursive(int n) {
    if (n == 0) {
        return 0;
    }
    return n % 10 + sum_recursive(n / 10);
}