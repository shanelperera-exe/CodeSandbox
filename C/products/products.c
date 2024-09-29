#include <stdio.h>

#define NUM_OF_PRODUCTS 10

int main(void) {
    char *products[10] = {
        "Apple", "Banana", "Orange", "Mango", "Grapes",
        "Peach", "Plum", "Pear", "Lemon", "Kiwi"
        };

    double prices[10] = {5.99, 12.50, 7.25, 10.00, 15.75, 9.99, 8.30, 6.50, 11.40, 4.99};

    int most_expensive = 0;
    int least_expensive = 0;

    for (int i = 0; i < NUM_OF_PRODUCTS; i++) {
        if (prices[i] > prices[most_expensive]) {
            most_expensive = i;
        }
        if (prices[i] < prices[least_expensive]) {
            least_expensive = i;
        }
    }

    printf("Most expensive product: %s ($%.2f)\n", products[most_expensive], prices[most_expensive]);
    printf("Least expensive product: %s ($%.2f)\n", products[least_expensive], prices[least_expensive]);

    return 0;
}
