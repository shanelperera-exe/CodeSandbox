#include<stdio.h>

int main(void) {
    double volume, time, rate;

    printf("Volume to be infused (ml): ");
    scanf("%lf", &volume);

    printf("Minutes over which to infuse: ");
    scanf("%lf", &time);

    // Calculate infusion rate in ml/hr
    rate = (volume / time) * 60;

    printf("VTBI: %.0f ml\n", volume);
    printf("Rate: %.0f ml/hr\n", rate);
    return 0;
}