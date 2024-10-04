#include <stdio.h>
#include <string.h>

#define NAME_BUFFER_SIZE 20
#define DATE_OF_BIRTH_BUFFER_SIZE 11
#define INPUT_BUFFER_SIZE 50

int main() {
    char input[INPUT_BUFFER_SIZE];
    char name[NAME_BUFFER_SIZE];
    char date_of_birth[DATE_OF_BIRTH_BUFFER_SIZE];

    while(1) {
        printf("Enter patient data: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        char *first_quote = strchr(input, '"');
        char *second_quote = strchr(first_quote + 1, '"');
        char *third_quote = strchr(second_quote + 1, '"');
        char *fourth_quote = strchr(third_quote + 1, '"');

        if (first_quote && second_quote && third_quote && fourth_quote) {
            int name_length = second_quote - first_quote - 1;
            int date_of_birth_length = fourth_quote - third_quote - 1;

            if (name_length >= NAME_BUFFER_SIZE || date_of_birth_length >= DATE_OF_BIRTH_BUFFER_SIZE) {
                printf("Error: Input exceeds buffer size.\n");
            } 
            else {
                strncpy(name, first_quote + 1, name_length);
                name[name_length] = '\0';

                strncpy(date_of_birth, third_quote + 1, date_of_birth_length);
                date_of_birth[date_of_birth_length] = '\0';

                printf("Data saved successfully.\n");
                break;
            }
        }
    }

    return 0;
}