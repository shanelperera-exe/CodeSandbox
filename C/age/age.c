#include<stdio.h>

int main(void) {
    int age;
    char sts;

    printf("Enter the age: ");
    scanf("%d", &age);

    if (age > 59) {
        printf("Enter status (W for Working, any other character for Retired): ");
        scanf(" %c", &sts);

        if (sts == 'W' || sts == 'w') {
            printf("Working Senior.\n");
        }
        else {
            printf("Retired Senior.\n");
        }
    }
    else if (age > 20) {
        printf("Adult.\n");
    }
    else if (age > 12) {
        printf("Teen.\n");
    }
    else {
        printf("Child.\n");
    }

    return 0;
}