#include <stdio.h>
#include <string.h>

int main(void) {
    char receipt[100] = "OrderID: #12345, Date: 2024-01-15";
    char order_id[10];
    int i, j = 0;
    
    for (i = 0; receipt[i] != '\0'; i++) {
        if (receipt[i] == '#') {
            strncpy(order_id, &receipt[i + 1], 5);
            order_id[5] = '\0';
            break;
        }
    }

    if (strlen(order_id) == 5) {
        printf("Order ID: %s\n", order_id);
    }

    return 0;
}