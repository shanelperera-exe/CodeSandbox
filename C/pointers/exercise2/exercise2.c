#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

void calculate_circle(float radius, float *circumference, float *area);

int main(void) {
    float radius, circumference, area;
    
    printf("Radius: ");
    scanf("%f", &radius);

    float *p_circumference = &circumference;
    float *p_area = &area;

    calculate_circle(radius, p_circumference, p_area);

    printf("Circumference: %.2f\n", circumference);
    printf("Area: %.2f\n", area);

    return 0;
}

void calculate_circle(float radius, float *circumference, float *area) {
    *circumference = 2 * PI * radius;
    *area = PI * pow(radius, 2);
}