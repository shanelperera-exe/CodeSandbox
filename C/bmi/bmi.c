#include<stdio.h>

int main(void) {
    float wt_lb, ht_in, BMI;

    printf("Enter weight in lbs: ");
    scanf("%f", &wt_lb);

    printf("Enter height in inches: ");
    scanf("%f", &ht_in);

    BMI = (wt_lb / (ht_in * ht_in)) * 703;

    if (BMI < 18.5) {
        printf("Underweight.\n");
    }
    else if (BMI >= 18.5 && BMI < 25) {
        printf("Normal Weight.\n");
    }
    else if (BMI >= 25 && BMI < 30) {
        printf("Overweight.\n");
    }
    else if (BMI >= 30) {
        printf("Obese\n");
    }
    return 0;
}