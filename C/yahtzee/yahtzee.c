#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_DICE 5

// Function declarations
void roll_dice(int dice[]);
void keep_dice(int dice[]);
void print_dice(int dice[]);
int calc_dice_score(int dice[]);
int score_single_numbers (int dice[], int number);

int main(void) {
    int dice[NUM_OF_DICE];
    roll_dice(dice);

    print_dice(dice);

    keep_dice(dice);

    int total_score = calc_dice_score(dice);
    printf("Total score: %d", total_score);
}

/* Rolling 5 dice*/
void roll_dice(int dice[]) {
    srand(time(NULL)); // Using current time as the seed2
    
    for (int i = 0; i < NUM_OF_DICE; i++) {
        dice[i] = rand() % 6 + 1; // Generating a random number between 1 and 6
    }
}

/* Choosing the dice to keep or re-roll */
void keep_dice(int dice[]) {
    int keep[NUM_OF_DICE];

    printf("Enter 1 to keep the die, 0 to re-roll:\n");
    for (int i = 0; i < NUM_OF_DICE; i++) {
        printf("Die %d (current value %d): ", i + 1, dice[i]);
        scanf("%d", &keep[i]);
    }
    for (int i = 0; i < NUM_OF_DICE; i++) {
        if (keep[i] == 0) {
            dice[i] = rand() % 6 + 1; // Re-rolling the unneeded dice
        }
    }

    print_dice(dice);

}

void print_dice(int dice[]) {
    for (int i = 0; i < 5; i++) {
        printf("%d ", dice[i]);
    }
    printf("\n");
}

int calc_dice_score(int dice[]) {
    int total_score = 0;

    for (int i = 1; i <= 6; i++) {
        total_score += score_single_numbers(dice, i);
    }
    return total_score;
}

int score_single_numbers (int dice[], int number) {
    int score = 0;
    for (int i = 0; i < NUM_OF_DICE; i++) {
        if (dice[i] == number) {
            score += number;
        }
    }
    return score;
}

// int score_three_of_a_kind() {
//     int score = 0;
//     for (int i = 0; i < NUM_OF_DICE; i++) {
        
//     }
// }