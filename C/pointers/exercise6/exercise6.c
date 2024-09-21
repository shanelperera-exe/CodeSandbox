#include <stdio.h>

void simplify_fraction(int *numerator, int *denominator);

int main(void) {
    int numerator, denominator;
    
    printf("Numerator: ");
    scanf("%d", &numerator);

    while (1) {
        printf("Denominator: ");
        scanf("%d", &denominator);

        if (denominator == 0) { 
            printf("Error! Denominator cannot be zero.\n");
            continue;
        }    
        else
            break;
    }

    simplify_fraction(&numerator, &denominator);

    printf("Simplified Fraction: %d/%d\n", numerator, denominator);
    
    return 0;
}

void simplify_fraction(int *numerator, int *denominator) {
    int num = *numerator;
    int deno = *denominator;

    while (deno != 0) {
        int temp = deno;
        deno = num % deno;
        num = temp;
    }

    int divisor = num;
    *numerator /= divisor;
    *denominator /= divisor;

}