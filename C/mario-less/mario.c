#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void) {
    int n;
    do {
        printf("Enter height: ");
        scanf("%d", &n);
    } while (n <= 0);

    for (int i = 1; i <= n; i++) {
        int spaces = n - i;
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
    printf("\n");
}
