#include <stdio.h>

void calculate(int *x, int *y, int *z);

int main(void) {
    int x, y, z;

    printf("x: ");
    scanf("%d", &x);

    printf("y: ");
    scanf("%d", &y);

    printf("z: ");
    scanf("%d", &z);

    int *px = &x;
    int *py = &y;
    int *pz = &z;

    calculate(px, py, pz);

    printf("Modified x (sum): %d\n", x);
    printf("Modified y (difference): %d\n", y);
    printf("Modified z (product): %d\n", z);

    return 0;
}

void calculate(int *x, int *y, int *z) {
    int original_x = *x;
    int original_y = *y;
    int original_z = *z;

    *x = original_x + original_y + original_z;
    *y = original_x - original_y;
    *z = original_x * original_z;
}