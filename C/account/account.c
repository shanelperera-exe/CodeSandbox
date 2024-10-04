#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 100
#define MAX_NAME_LEN 50
#define MAX_ACCOUNT_NUMBER_LEN 50

int main(void) {
    char user_input[MAX_INPUT_LEN];
    char name[MAX_NAME_LEN];
    char account_number[MAX_ACCOUNT_NUMBER_LEN];

    printf("Enter account details: ");

    fgets(user_input, sizeof(user_input), stdin);
    user_input[strcspn(user_input, "\n")] = '\0';

    int i = 0;
    while (user_input[i] != ',' && user_input[i] != '\0' && i < MAX_NAME_LEN - 1) {
        name[i] = user_input[i];
        i++;
    }
    name[i] = '\0';

    if (user_input[i] == ',') {
        i++;
        while (user_input[i] == ' ') {
            i++;
        }
    }

    int j = 0;
    while (user_input[i] != '\0' && j < MAX_ACCOUNT_NUMBER_LEN - 1) {
        account_number[j] = user_input[i];
        i++;
        j++;
    }
    account_number[j] = '\0';

    printf("Name: %s\n", name);
    printf("Account Number: %s\n", account_number);
    return 0;

}