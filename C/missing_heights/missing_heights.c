#include<stdio.h>

int main(void) {
    float height1, height2, height3, average, total, missing1, missing2;

    printf("Enter the height of three known people: ");
    scanf("%f %f %f", &height1, &height2, &height3);

    printf("Enter the average height: ");
    scanf("%f", &average);

    float sum = height1 + height2 + height3;

    total = average * 5;

    float total_missing_heights = total - sum;

    missing1 = missing2 = total_missing_heights / 2;

    printf("Missing heights are %.2f and %.2f\n", missing1, missing2);
    return 0;
}