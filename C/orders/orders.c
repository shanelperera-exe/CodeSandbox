#include <stdio.h>

int main(void) {
    char status;
    for (int order_num = 1; order_num <= 5; order_num++) {
        printf("Enter status of order %d: ", order_num);
        scanf(" %c", &status);

        switch (status) {
            case 'I':
                printf("Skipping order %d\n", order_num);
                continue;

            case 'S':
                printf("Stopping at order %d\n", order_num);
                return 0;
                break;

            case 'V':
                printf("Processing order %d\n", order_num);
        }
    }
}
