#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_DICE 5
#define NUM_OF_SCORING_CATAGORIES 13

/* Function declarations */
void roll_dice(int dice[]);
void keep_dice(int dice[], int rolls_left);
void display_dice(int dice[]);
void choose_scoring_category(int dice[], int used_categories[], int player_scores[]);
void display_total_score(int player_scores[]);
// Scoring functions
int score_single_numbers (int dice[], int number);
int score_three_of_a_kind(int dice[]);
int score_four_of_a_kind(int dice[]);
int score_full_house(int dice[]);
int score_small_straight(int dice[]);
int score_large_straight(int dice[]);
int score_chance(int dice[]);
int score_yahtzee(int dice[]);

int main(void) {
    int dice[NUM_OF_DICE];
    int roll_count; // Counter for the number of rolls
    const int roll_limit = 3; // Defining the roll limit
    int player_scores[NUM_OF_SCORING_CATAGORIES] = {0}; // Array to store human player scores for each category
    int used_categories[NUM_OF_SCORING_CATAGORIES] = {0}; // Array to track used categories
    int computer_scores[NUM_OF_SCORING_CATAGORIES] = {0}; // Array to store computer AI scores for each category

    srand(time(NULL)); // Seed the random number generator using current time

    for (int round = 0; round < NUM_OF_SCORING_CATAGORIES; round++) {
        printf("ROUND %d\n", round + 1); // Displaying round number
        roll_count = 0; // Resetting the number of rolls for each round 

        // Initial dice roll
        roll_dice(dice); // Roll all dice
        display_dice(dice); // Show the initial roll

        // Loop until the player reaches the maximum rolls allowed
        while (1) {
            if (roll_count < roll_limit) {
                // Prompt the user to choose to re-roll or choose a scoring category
                int choice;
                printf("Choose an option >>> \n");
                printf("1. Re-roll\n");
                printf("2. Choose scoring category\n");
                printf("Enter your choice (1 or 2): ");
                scanf("%d", &choice);

                if (choice == 1) {
                    if (roll_count < roll_limit) { // Check if re-rolls are still allowed
                        int rolls_left = roll_limit - roll_count; // Calculate remaining rolls
                        keep_dice(dice, rolls_left); // Ask the player which dice to keep or re-roll
                        roll_count++; // Increment roll count after each roll
                    }
                }
                else if (choice == 2) {
                    choose_scoring_category(dice, used_categories, player_scores);
                    break; // Exit the loop after scoring
                }
                else {
                    printf("Invalid choice! Please enter 1 or 2.\n");
                    continue; // Continue loop until a valid input has entered
                }
            }
            else {
                // Only allow scoring category selection if maximum rolls are exceeded
                printf("You have reached the maximum number of rolls for this turn.\n");
                choose_scoring_category(dice, used_categories, player_scores);
                break; // Exit the loop after scoring
            }
        }
        display_total_score(player_scores);
    }
    return 0;
}

/* Rolling 5 dice*/
void roll_dice(int dice[]) {
    for (int i = 0; i < NUM_OF_DICE; i++) {
        dice[i] = rand() % 6 + 1; // Generating a random number between 1 and 6
    }
}

/* Choosing the dice to keep or re-roll */
void keep_dice(int dice[], int rolls_left) {
    int keep[NUM_OF_DICE];

    // Asking user which dice to be ee-rolled and which dice to keep. (1 to keep, 0 to re-roll)
    printf("Enter 1 to keep the die, 0 to re-roll:\n");
    for (int i = 0; i < NUM_OF_DICE; i++) {
        int valid_input = 0; // Flag to ckeck if input is valid
        while (!valid_input) {
            printf("Die %d (current value %d): ", i + 1, dice[i]);
            scanf("%d", &keep[i]);

            // Check if the input is either 0 or 1
            if (keep[i] == 0 || keep[i] == 1) {
                valid_input = 1; 
            }
            else {
                printf("Invalid input! Please enter 1 to keep or 0 to re-roll.\n");
                continue; // Continue prompting for valid input
            }
        }
    }
    // Re- rolling the unkept dice
    for (int i = 0; i < NUM_OF_DICE; i++) {
        if (keep[i] == 0) { // Check if the die is marked for re-roll
            dice[i] = rand() % 6 + 1; // Re-rolling the unneeded dice
        }
    }

    display_dice(dice); // Print the new values of the dice after re-rolling

}

/* Printing dice values */
void display_dice(int dice[]) {
    for (int i = 0; i < 5; i++) {
        printf("%d ", dice[i]); // Print each die's value
    }
    printf("\n"); // New line after printing all dice
}

/* Allow Player to choose a scoring catagory */
void choose_scoring_category(int dice[], int used_categories[], int player_scores[]) {
    int choice;

    printf("Choose a scoring catagory:\n");
    printf("--------------------------\n");
    printf("1.  Ones\n");
    printf("2.  Twos\n");
    printf("3.  Threes\n");
    printf("4.  Fours\n");
    printf("5.  Fives\n");
    printf("6.  Sixes\n");
    printf("7.  Three of a kind\n");
    printf("8.  Four of a kind\n");
    printf("9.  Full House\n");
    printf("10. Small Straight\n");
    printf("11. Large Straight\n");
    printf("12. Chance\n");
    printf("13. YAHTZEE\n");
    printf("--------------------------\n");

    int valid_choice = 0; // Flag to check if choice is valid
    while (!valid_choice) {
        printf("Choice: ");
        scanf("%d", &choice); // Get the user's choice

        // Check if the input is valid (between 1 and 13)
        if (choice >= 1 && choice <= NUM_OF_SCORING_CATAGORIES) {
            // Check if the category has already been used
            if (used_categories[choice - 1] == 0) {
                valid_choice = 1; // Input is valid
            }
            else {
                printf("You have already scored in this category! Choose another category.\n");
            }
        }
        else {
            printf("Invalid choice! Please choose a catagory between 1 and 13.\n");
        }
    }

    int score = 0; // Initialize score variable

    // Determine the score based on the chosen category
    switch (choice) {
    case 1:
        score = score_single_numbers(dice, 1);
        break;
    case 2:
        score = score_single_numbers(dice, 2);
        break;
    case 3:
        score = score_single_numbers(dice, 3);
        break;
    case 4:
        score = score_single_numbers(dice, 4);
        break;
    case 5:
        score = score_single_numbers(dice, 5);
        break;
    case 6:
        score = score_single_numbers(dice, 6);
        break;
    case 7:
        score = score_three_of_a_kind(dice);
        break;
    case 8:
        score = score_four_of_a_kind(dice);
        break;
    case 9:
        score = score_full_house(dice);
        break;
    case 10:
        score = score_small_straight(dice);
        break;
    case 11:
        score = score_large_straight(dice);
        break;
    case 12:
        score = score_chance(dice);
        break;
    case 13:
        score = score_yahtzee(dice);
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }

    player_scores[choice - 1] = score; // Store the score for the chosen category
    used_categories[choice - 1] = 1; // Mark the category as used
    
    printf("%d points scored.\n", score); // Display the score
}

/* Scoring for single numbers (1 to 6) */
int score_single_numbers (int dice[], int number) {
    int score = 0; // Initialize score
    for (int i = 0; i < NUM_OF_DICE; i++) {
        if (dice[i] == number) { // Check if die value matches the chosen number
            score += number; // Add to the score
        }
    }
    return score; // Return the total score for that number
}

/* Three of a kind */
int score_three_of_a_kind(int dice[]) {
    for (int i = 1; i <= 6; i++) { // Check for each possible die value (1-6)
        int count = 0; // Count occurrences of the die value
        for (int j = 0; j < NUM_OF_DICE; j++) {
            if (dice[j] == i) {
                count++; // Increment count if die value matches
            }
            
        }
        if (count >= 3) { // If we have at least three of this die value
            int sum = 0; // Initialize sum for total score
            for (int j = 0; j < NUM_OF_DICE; j++) {
                sum += dice[j]; // Sum all dice values for scoring
            }
            return sum; // Return total score
        }
        
    }
    return 0; // Returning 0 when no three of a kind found.
}

/* Four of a kind */
int score_four_of_a_kind(int dice[]) {
    for (int i = 1; i <= 6; i++) { // Check for each possible die value (1-6)
        int count = 0; // Count occurrences of the die value
        for (int j = 0; j < NUM_OF_DICE; j++) {
            if (dice[j] == i) {
                count++; // Increment count if die value matches
            }
        }
        if (count >= 4) { // If we have at least four of this die value
            int sum = 0; // Initialize sum for total score
            for (int j = 0; j < NUM_OF_DICE; j++) {
                sum += dice[j]; // Sum all dice values for scoring
            }
            return sum; // Return total score
        }
    }
    return 0; // Returning 0 if no four of a kind found.
}

/* Full House */
int score_full_house(int dice[]) {
    int count[7] = {0}; // To store how many times each die value(from 1 to 6) appears (occurrences).
    // Initialized with zeroes.

    for (int i = 0; i < NUM_OF_DICE; i++) {
        count[dice[i]]++; // Increment the count for this die value
    }

    int three_of_a_kind = 0; // Flag to check for three of a kind
    int pair = 0; // Flag to check for a pair

    for (int i = 1; i <= 6; i++) { // Check the counts
        if (count[i] == 3) {
            three_of_a_kind = 1; // Found three of a kind
        }
        if (count[i] == 2) {
            pair = 1; // Found a pair
        }
    }
    if (three_of_a_kind && pair) {
        return 25;  // Return 25 points for a Full House
    }
    return 0; // Returning 0 if no full house found.
}

/* Small Straight */
int score_small_straight(int dice[]) {
    int count[7] = {0}; // To track occurrences of die values
    for (int i = 0; i < NUM_OF_DICE; i++) {
        count[dice[i]]++; // Count occurrences
    }

    // Check for a small straight: (1-2-3-4), (2-3-4-5), or (3-4-5-6)
    if ((count[1] && count[2] && count[3] && count[4]) || (count[2] && count[3] && count[4] && count[5]) || (count[3] && count[4] && count[5] && count[6])) {
        return 30; // Return 30 points for a small straight
    }
    return 0; // Returning 0 if no small straight found.
}

/* Large Straight */
int score_large_straight(int dice[]) {
    int count[7] = {0}; // To track occurrences of die values
    for (int i = 0; i < NUM_OF_DICE; i++) {
        count[dice[i]]++; // Count occurrences
    }

    // Check for a large straight: (1-2-3-4-5) or (2-3-4-5-6)
    if ((count[1] && count[2] && count[3] && count[4] && count[5]) || (count[2] && count[3] && count[4] && count[5] && count[6])) {
        return 40; // Return 40 points for a large straight
    }
    return 0; // Returning 0 if no large straight found
}

/* Chance */
int score_chance(int dice[]) {
    int sum = 0; // Initialize sum for total score
    for (int i = 0; i < NUM_OF_DICE; i++) {
        sum += dice[i]; // Sum all dice values for scoring
    }
    return sum; // Return total score
}

/* Yahtzee */
int score_yahtzee(int dice[]) {
    for (int i = 1; i <= 6; i++) { // Check for each possible die value (1-6)
        int count = 0; // Count occurrences of the die value
        for (int j = 0; j < NUM_OF_DICE; j++) {
            if (dice[j] == i) {
                count++; // Increment count if die value matches
            }
        }
        if (count == 5) { // If we have all five of this die value
            return 50; // Return 50 points for a Yahtzee
        }
    }
    return 0; // Returning 0 if no Yahtzee found.
}

void display_total_score(int player_scores[]) {
    int total_score = 0;
    for (int i = 0; i < NUM_OF_SCORING_CATAGORIES; i++) {
        total_score += player_scores[i];
    }
    printf("Total Score: %d\n", total_score);
}

void print_score_table(int player_scores[], int computer_scores[]) {
    
}