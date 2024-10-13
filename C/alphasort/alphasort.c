#include <stdio.h>
#include <string.h>

#define NUM_OF_STRINGS 3
#define MAX_LENGTH 50

int main(void) {
    char list[NUM_OF_STRINGS][MAX_LENGTH];
    char temp[MAX_LENGTH];

    for (int i = 0; i < NUM_OF_STRINGS; i++) {
        printf("Enter string %d: ", i + 1);
        fgets(list[i], MAX_LENGTH, stdin);
        list[i][strcspn(list[i], "\n")] = '\0';            
    }

    for (int i = 0; i < NUM_OF_STRINGS - 1; i++) {
        for (int j = i + 1; j < NUM_OF_STRINGS; j++) {
            if (strcmp(list[i], list[j]) > 0) {
                strcpy(temp, list[i]);
                strcpy(list[i], list[j]);
                strcpy(list[j], temp);
            }
        }
    }

    printf("Sorted list: ");
    for (int i = 0; i < NUM_OF_STRINGS; i++) {
        printf("%s ", list[i]);
    }
    printf("\n");

    return 0;
    
}