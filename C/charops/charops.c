#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 200

int main(void) {
    int alphabets = 0;
    int digits = 0;
    int special_chars = 0;

    char user_input[MAX_LENGTH];

    printf("Enter a string: ");
    fgets(user_input, MAX_LENGTH, stdin);

    for (int i = 0; i < strlen(user_input); i++) {
        if (isalpha(user_input[i])) {
            alphabets++;
        }
        else if (isdigit(user_input[i])) {
            digits++;
        }
        else if (ispunct(user_input[i])) {
            special_chars++;
        }
    }

    printf("Alphabets: %d, Digits: %d, Special characters: %d\n", alphabets, digits, special_chars);

    return 0;
}