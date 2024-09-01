#include <stdio.h>

int main(void) {
    int user_in;

    do {
        printf("Please enter a positive number: ");
        scanf("%d", &user_in);
    } while(user_in < 0);
    printf("You entered: %d\n", user_in);
    return 0;
}