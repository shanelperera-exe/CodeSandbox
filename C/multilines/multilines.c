#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 250

int main(void) {
    char lines[MAX_LINES][MAX_LENGTH];
    int line_count = 0;
    char formatted_line[MAX_LENGTH + 5];
    
    printf("Enter up to %d lines of text. Press Enter on an empty line to stop.\n", MAX_LINES);

    while (line_count < MAX_LINES) {
        printf("Line %d: ", line_count + 1);
        fgets(lines[line_count], MAX_LENGTH, stdin);

        lines[line_count][strcspn(lines[line_count], "\n")] = '\0';

        if (strlen(lines[line_count]) == 0) {
            break;
        }

        line_count++;
    }

    printf("\nFormatted Output:\n");

    for (int i = 0; i < line_count; i++) {
        sprintf(formatted_line, "%d. %s", i + 1, lines[i]);
        printf("%s\n", formatted_line);
    }

    return 0;
}