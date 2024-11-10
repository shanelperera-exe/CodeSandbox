#include <stdio.h>

typedef struct {
    int width;
    int height;
} rectangle_t;

void update_rectangle(rectangle_t *rectangle);

int main(void) {
    rectangle_t rectangle;

    update_rectangle(&rectangle);

    printf("Updated Rectangle - Width: %d, Height: %d\n", rectangle.width, rectangle.height);

    return 0;
}

void update_rectangle(rectangle_t *rectangle) {
    printf("Width: ");
    scanf("%d", &rectangle->width);
    printf("Height: ");
    scanf("%d", &rectangle->height);
}

