#include <stdio.h>
#include <math.h>

void instruct(void);
void convert(void);

int main(void) {
    instruct();
    convert();

    return 0;
}

void instruct(void) {
    printf("This program takes three integer type inputs from a user and prints the corresponding decimal value\n");
}

void convert(void) {
    int bin1, bin2, bin3, dec;
    
    printf("Enter the first integer: ");
    scanf("%d", &bin1);
    printf("Enter the second integer: ");
    scanf("%d", &bin2);
    printf("Enter the third integer: ");
    scanf("%d", &bin3);

    dec = bin3 * pow(2,2) + bin2 * pow(2,1) + bin1 * pow(2,0);
    printf("Decimal value: %d\n", dec);
} 