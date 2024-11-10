#include <stdio.h>
#include <string.h>

#define NUM_OF_STUDENTS 2
#define NAME_SIZE 50

int main(void) {
    char students[NUM_OF_STUDENTS][NAME_SIZE];
    int id[NUM_OF_STUDENTS];
    int scores[NUM_OF_STUDENTS];

    for (int i = 0; i < NUM_OF_STUDENTS; i++) {
        printf("Student %d\n", i + 1);
        printf("Name: ");
        fgets(students[i], NAME_SIZE, stdin);
        students[i][strcspn(students[i], "\n")] = '\0';

        printf("ID: ");
        scanf("%d", &id[i]);

        printf("Score: ");
        scanf("%d", &scores[i]);
        getchar();
        printf("\n");
    }
    
    int id_search;

    printf("Enter student id: ");
    scanf("%d", &id_search);
    for (int i = 0; i < NUM_OF_STUDENTS; i++) {
        if (id_search == id[i]) {
            printf("%s (%d), Score: %d\n", students[i], id[i], scores[i]);
            break;
        }
    }

    return 0;
}