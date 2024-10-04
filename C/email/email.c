#include <stdio.h>
#include <string.h>

int main(void) {
    char greeting[50] = "Hello,";
    char body_message[100] = "Your order has been shipped.";
    char closing[75] = "Regards, XYZ Company";

    char email[250] = "";

    strcat(email, greeting);
    strcat(email, " ");
    strncat(email, body_message, 250 - strlen(email - 1));
    strcat(email, " ");
    strncat(email, closing, 250 - strlen(email) - 1);

    printf("%s\n", email);

    return 0;
}

