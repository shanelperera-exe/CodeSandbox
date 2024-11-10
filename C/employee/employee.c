#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
#define NUM_OF_EMPLOYEES 5

typedef struct {
    char name[BUFFER_SIZE];
    int id;
    int salary; 
} employee_t;

void find_highest_salary(employee_t employees[]);

int main(void) {
    employee_t employees[NUM_OF_EMPLOYEES];

    for (int i = 0; i < 2; i++) {
        printf("Employee %d\n", i + 1);
        printf("Name: ");
        fgets(employees[i].name, BUFFER_SIZE, stdin);
        employees[i].name[strcspn(employees[i].name, "\n")] = '\0';
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Salary: ");
        scanf("%d", &employees[i].salary);
        getchar();
        printf("\n");
    }

    find_highest_salary(employees);

    return 0;
}

void find_highest_salary(employee_t employees[]) {
    int highest_salary = employees[0].salary;
    int highest_index = 0;

    for (int i = 0; i < NUM_OF_EMPLOYEES; i++) {
        if (employees[i].salary < highest_salary) {
            highest_salary = employees[i].salary;
            highest_index = 1;
        }
    }

    printf("Highest Salary: %s, ID: %d, Salary: %d\n", employees[highest_index].name, employees[highest_index].id, employees[highest_index].salary);
}

