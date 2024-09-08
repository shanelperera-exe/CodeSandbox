#include<stdio.h>

int main(void) {
    double gpa;

    printf("Enter the GPA: ");
    scanf("%lf", &gpa);

    if (gpa >= 0.0 && gpa <= 4.0) {
        if (gpa >= 0.0 && gpa <= 0.99) {
            printf("Failed semester-registration suspended.\n");
        }
        else if (gpa >= 1.0 && gpa <= 1.99) {
            printf("On probation for next semester.\n");
        }
        else if (gpa >= 3.0 && gpa <= 3.49) {
            printf("Dean's list for semester.\n");
        }
        else if (gpa >= 3.5 && gpa <= 4.0) {
            printf("Highest honours for semester.\n");
        }
    }
    else {
        printf("Invalid GPA.\n");
    }
    return 0;
}