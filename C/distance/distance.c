#include <stdio.h>
#include <math.h>

void instruct(void);
double calculateDistance(void);
void printDistance(double dis);

double distance;

int main(void) {
    instruct();
    distance = calculateDistance();
    printDistance(distance);
    return 0;
}

void instruct(void) {
    printf("This program calculates the distance between two points in a 2D plane using functions\n");
}

double calculateDistance(void) {
    int x1, y1, x2, y2;
    printf("Enter the coordinates of two points in the format of x,y\n");
    printf("Enter the first coordinate: ");
    scanf("%d,%d", &x1, &y1);
    printf("Enter the second coordinate: ");
    scanf("%d,%d", &x2, &y2);


    distance = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    return distance;
}

void printDistance(double dis) {
    printf("Distance: %.2f\n", dis);
}