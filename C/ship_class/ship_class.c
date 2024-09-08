#include<stdio.h>

int main(void) {
    char serial_num[11];
    char class_id;

    printf("Enter the ship's serial number: ");
    scanf("%s", serial_num);

    class_id = serial_num[0];

    switch (class_id) {
    case 'B':
    case 'b':
        printf("Battleship\n");
        break;
    case 'C':
    case 'c':
        printf("Cruiser\n");
        break;
    case 'D':
    case 'd':
        printf("Destroyer\n");
        break;
    case 'F':
    case 'f':
        printf("Frigate\n");
        break;
    default:
        printf("Unknown Ship Class.\n");
    }
    return 0;
}