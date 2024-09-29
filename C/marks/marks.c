#include <stdio.h>

float calc_avg(int marks[], int size);

int main(void) {
    int size = 10;
    int marks[size];
    
    for (int i = 0; i < size; i++) {
        printf("Enter the score of student %d: ", i+1);
        scanf("%d", &marks[i]);
    }
    
    float average = calc_avg(marks, size);
    printf("Average: %.2f\n", average);
    
    printf("Students scoring above average: ");
    for (int j = 0; j < size; j++) {
        if (marks[j] > average) {
            printf("%d ", marks[j]);
        }
    }
    printf("\n");
    return 0;
}

float calc_avg(int marks[], int size) {
    int sum = 0;
    for (int j = 0; j < size; j++) {
        sum += marks[j];
    }
    
    float avg = (float) sum / size;
    return avg;
}
