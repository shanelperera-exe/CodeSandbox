#include<stdio.h>

int main(void) {
    float perimeter, length, width;
    
    printf("Enter the perimeter of the fence: ");
    scanf("%f", &perimeter);

    /* Perimeter = 2(length + width)
                 = 2l(1 + (3/4))
                 = 2l(7/4)
               P = l (7/2)
               l = (2/7)P           */

    length = (2.0/7.0) * perimeter;
    width = (3.0/4.0) * length;

    printf("Length of the fence: %.2f\n", length);
    printf("Width of the fence: %.2f\n", width);
    return 0;
}