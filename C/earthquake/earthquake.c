#include <stdio.h>

int main(void) {
    float n;

    printf("Enter the Richter scale number of the earthquake: ");
    scanf("%f", &n);

    // Using a switch statement to handle this problem is not ideal because switch statements typically work with discrete values (like integers or characters) rather than ranges of values.
    if (n < 5.0) {
        printf("Little or no damage.\n");
    }
    else if (n >= 5.0 && n <= 5.5) {
        printf("Some damage.\n");
    }
    else if (n >= 5.5 && n <= 6.5) {
        printf("Serious damage: walls may crack or fall.\n");
    }
    else if (n >= 6.5 && n <= 7.5) {
        printf("Disaster: houses and buildings may collapse.\n");
    }
    else if (n > 7.5) {
        printf("Catastrophe: most buildings destroyed.\n");
    }

    return 0;
}