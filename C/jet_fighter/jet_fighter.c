#include<stdio.h>

int main(void) {
    float takeoff_speed_kmh,distance_m, takeoff_speed_ms, acceleration, time;

    printf("Enter the jet's takeoff speed (km/h): ");
    scanf("%f",&takeoff_speed_kmh);

    printf("Enter the distance (m): ");
    scanf("%f",&distance_m);

    // Converting takeoff speed from kms to ms
    takeoff_speed_ms = (takeoff_speed_kmh * 1000.0) / 3600.0;

    // Calculate acceleration
    acceleration = (2 * distance_m) / (takeoff_speed_ms * takeoff_speed_ms);
    
    // Calculating time
    time = takeoff_speed_ms / acceleration;

    printf("Acceleration: %.2f ms^-2\n", acceleration);
    printf("Time: %.2f seconds\n", time);
    return 0;
}