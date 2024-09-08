#include<stdio.h>
#include<math.h>

void instruct();
int calculateDiscriminant();
void calculateRoots(int a, int b, int discriminant);

int a, b, c, discriminant;
float root1, root2;

int main(void) {
    instruct();
    discriminant = calculateDiscriminant();
    calculateRoots(a, b, discriminant);
    return 0;
}

void instruct() {
    printf("This program solves quadratic equations of the form ax^2+bx+c=0\n");
}

int calculateDiscriminant(void) {
    printf("Enter the coefficients as a, b and c.\n");
    
    printf("Enter 'a': ");
    scanf("%d", &a);

    printf("Enter 'b': ");
    scanf("%d", &b);

    printf("Enter 'c': ");
    scanf("%d", &c);

    discriminant = pow(b, 2) - 4 * a * c;

    return discriminant;
}

void calculateRoots(int a, int b, int discriminant) {
    if (a > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
    }

    printf("Roots: %.3f and %.3f\n", root1, root2);
}
