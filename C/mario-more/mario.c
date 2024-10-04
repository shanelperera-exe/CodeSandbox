#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void) {
    int height;
    do {
        printf("Enter height: ");
        scanf("%d", &height);
    } while (height <= 0);

    for (int i = 1; i <= height; i++) {
        int spaces = height - i;
        int bricks = i;

        print_row(spaces, bricks);
    }
    return 0;

}

void print_row(int spaces, int bricks) {
    for (int j = 1; j <= spaces; j++) {
        printf(" ");
    }
    for (int i = 1; i <= bricks; i++) {
        printf("#");
    }

    printf("  ");

    for (int n = 1; n <= bricks; n++) {
        printf("#");
    }
    printf("\n");
}
