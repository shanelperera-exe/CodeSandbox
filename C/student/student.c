#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

typedef struct {
    char name[BUFFER_SIZE];
    int age;
    double gpa;
} student_t;

student_t get_student(void);

int main(void) {
    student_t current_student = get_student();

    printf("\nStudent Name: %s, Age: %d, GPA: %.1f\n", current_student.name, current_student.age, current_student.gpa);

    return 0;
}

student_t get_student(void) {
    student_t student;

    printf("Name: ");
    fgets(student.name, BUFFER_SIZE, stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("Age: ");
    scanf("%d", &student.age);

    printf("GPA: ");
    scanf("%lf", &student.gpa);

    return student;
}