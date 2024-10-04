#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 3

void convert_to_lower(char *user_input);

int main(void) {
    char catalog[MAX_PRODUCTS][50] = {"Camera", "Camp Stove", "Candle"};
    char user_input[50];
    char lower_catalog[50];

    printf("Search: ");
    scanf("%s", user_input);

    convert_to_lower(user_input);


    for (int i = 0; i < MAX_PRODUCTS; i++) {
        strcpy(lower_catalog, catalog[i]);
        convert_to_lower(lower_catalog);

        if (strstr(lower_catalog, user_input)) {
            printf("%s\n", catalog[i]);
        }
    }
    printf("\n");

    return 0;
}

void convert_to_lower(char *search_str) {
    for (int j = 0; search_str[j]; j++) {
        search_str[j] = tolower(search_str[j]);
    }
}