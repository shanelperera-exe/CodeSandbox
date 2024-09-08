#include <stdio.h>

int main(void) {
    int user_in;
    while (1)
    {
        printf("You entered: ");
        scanf("%d", &user_in);

        if (user_in == 0) {
            printf("Exiting loop.\n");
            break;
        }
    }
    return 0;
}