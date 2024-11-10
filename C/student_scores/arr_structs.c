#include <stdio.h>
#include <string.h>

#define NUM_OF_STUDENTS 2
#define NAME_SIZE 50

typedef struct {
    char name[NAME_SIZE];
    int id;
    int score;
} student_t;

int main(void) {
    student_t student[NUM_OF_STUDENTS];

    for (int i = 0; i < NUM_OF_STUDENTS; i++) {
        printf("Student %d\n", i+1);
        printf("Name: ");
        fgets(student[i].name, NAME_SIZE, stdin);
        student[i].name[strcspn(student[i].name, "\n")] = '\0';
        
        printf("ID: ");
        scanf("%d", &student[i].id);

        printf("Score: ");
        scanf("%d", &student[i].score);
        
        getchar();
        printf("\n");
    }

    int id_search;

    printf("Enter student id: ");
    scanf("%d", &id_search);
    
    for (int i = 0; i < NUM_OF_STUDENTS; i++) {
        if (id_search == student[i].id) {
            printf("%s (%d), Score: %d\n", student[i].name, student[i].id, student[i].score);
            break;
        }
    }

    return 0;
}