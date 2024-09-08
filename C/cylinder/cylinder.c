#include <stdio.h>
#include <math.h>

const double PI = 3.14;

void instruct(void);
double calculateCylinderVolume(double r, double h);
double calculateCylinderSurfaceArea(double r, double h);
void printCylinderDetails(double vol, double area);

int main(void) {
    double r, h, vol, area;
    
    instruct();
    printf("Enter the radius(m): ");
    scanf("%lf", &r);
    printf("Enter the height(m): ");
    scanf("%lf", &h);
    
    vol = calculateCylinderVolume(r, h);
    area = calculateCylinderSurfaceArea(r, h);
    printCylinderDetails(vol, area);
    
    return 0;
}

void instruct(void) {
    printf("This program calculates the volume and surface area of a cylinder\n");
}

double calculateCylinderVolume(double r, double h) {
    return PI * pow(r, 2) * h;
}

double calculateCylinderSurfaceArea(double r, double h) {
    return 2 * PI * r * (r + h);
}

void printCylinderDetails(double vol, double area) {
    printf("Volume of the cylinder: %.2f m^3\n", vol);
    printf("Area of the cylinder: %.2f m^2\n", area);
}
