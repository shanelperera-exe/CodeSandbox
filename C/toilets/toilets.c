#include<stdio.h>
#define NEW_TOILET_COST 150

int main(void) {
    int population;
    double num_of_toilets, current_usage_of_water_per_day, new_usage_of_water_per_day, water_saved_per_day, new_toilet_cost;

    // prompt for the population
    printf("Enter the population of the community: ");
    scanf("%d", &population);

    // calculating the amount of toilets
    num_of_toilets = population / 3.0;

    // calculating the current usage of water
    current_usage_of_water_per_day = num_of_toilets * 15 * 14;

    // calculating the new usage of water
    new_usage_of_water_per_day = num_of_toilets * 2 * 14;

    // calculating the new usage of water
    water_saved_per_day = current_usage_of_water_per_day - new_usage_of_water_per_day;

    // calculating the cost of installation of new toilets
    new_toilet_cost = num_of_toilets * NEW_TOILET_COST;

    printf("Magnitude of the water saved: %.2lf litres/day\n", water_saved_per_day);
    printf("Total cost of installation of new toilets: %.2lf $\n", new_toilet_cost);
    return 0;
}