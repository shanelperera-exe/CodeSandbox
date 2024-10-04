#include <stdio.h>
#include <string.h>
#include <ctype.h>

void format_names(char *first_name, char *last_name);

int main(void) {
    char name[50];
    char first_name[25];
    char last_name[25];

    printf("Enter customer name: ");
    fgets(name, sizeof(name), stdin);

    int i = 0, j = 0;
    
    while (name[i] != ' ' && name[i] != '\0' && name[i] != '\n') {
        first_name[j] = name[i];
        j++;
        i++;
    }
    first_name[j] = '\0';

    while (name[i] == ' ') {
        i++;
    }
    
    j = 0;
    while (name[i] != '\0' && name[i] != '\n') {
        last_name[j] = name[i];
        j++;
        i++;
    }
    last_name[j] = '\0';

    format_names(first_name, last_name);

    if (last_name[0] == '\0') {
        printf("%s N/A\n", first_name);
    }
    else {
        printf("%s %s\n", first_name, last_name);
    }
    
    return 0;
}

void format_names(char *first_name, char *last_name) {
    first_name[0] = toupper(first_name[0]);
    
    for (int i = 1; i < strlen(first_name); i++) {
        first_name[i] = tolower(first_name[i]);
    }

    last_name[0] = toupper(last_name[0]);
    
    for (int j = 1; j < strlen(last_name); j++) {
        last_name[j] = tolower(last_name[j]);
}

}