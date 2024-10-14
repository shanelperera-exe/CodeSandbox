#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Defining constants
#define NUM_OF_DICE 5
#define NUM_OF_SCORING_CATEGORIES 13
#define FULL_HOUSE_POINTS 25
#define SMALL_STRAIGHT_POINTS 30
#define LARGE_STRAIGHT_POINTS 40
#define BONUS_POINTS_THRESHOLD 63
#define BONUS 35
#define YAHTZEE_SCORE 50
#define MULTI_YAHTZEE_BONUS 100

/* Function declarations */
void roll_dice(int dice[]);
void keep_dice(int dice[], int rolls_left);
void display_dice(int dice[]);
int score_based_on_categories(int choice, int dice[]);
void player_choose_scoring_category(int dice[], int player_used_categories[], int player_scores[]);
void computer_choose_scoring_category(int dice[], int computer_scores[], int computer_used_categories[]);
void display_score_table(int player_scores[], int computer_scores[], int game_over);
int calc_score_of_singles(int scores[]);
int check_bonus(int scores[]);
int calc_total_score(int scores[]);
void player_turn(int dice[], int roll_limit, int player_used_categories[], int player_scores[]);
void computer_turn(int dice[], int roll_limit, int computer_used_categories[], int computer_scores[]);
void decide_dice_to_reroll(int dice[], int reroll[]);
char* convert_score_to_str(int score, char *score_str);
int all_singles_scored(int scores[]);
// Scoring functions
int score_single_numbers (int dice[], int number);
int score_three_of_a_kind(int dice[]);
int score_four_of_a_kind(int dice[]);
int score_full_house(int dice[]);
int score_small_straight(int dice[]);
int score_large_straight(int dice[]);
int score_chance(int dice[]);
int score_yahtzee(int dice[]);
void player_choose_lower_category(int dice[], int player_used_categories[], int player_scores[]);
// Additional score functions
int check_bonus(int player_scores[]);
void player_handle_multiple_yahtzees(int dice[], int player_used_categories[], int player_scores[]);
void joker(int dice[], int used_categories[], int scores[], int yahtzee_value);

int main(void) {
    int dice[NUM_OF_DICE];
    int roll_count; // Counter for the number of rolls
    const int roll_limit = 3; // Defining the roll limit
    int player_scores[NUM_OF_SCORING_CATEGORIES] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Array to store human player scores for each category
    int player_used_categories[NUM_OF_SCORING_CATEGORIES] = {0}; // Array to track used categories by the player
    int computer_used_categories[NUM_OF_SCORING_CATEGORIES] = {0}; // Array to track used categories by the player
    int computer_scores[NUM_OF_SCORING_CATEGORIES] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Array to store computer AI scores for each category

    srand(time(NULL)); // Seed the random number generator using current time

    int game_over = 0; // Flag to check if the game has ended (Initializing game_over to false)

    for (int round = 0; round < NUM_OF_SCORING_CATEGORIES; round++) {
        display_score_table(player_scores, computer_scores, game_over); // Display the score table at the beginning of the each round
        printf("*** ROUND %d ***\n", round + 1); // Displaying round number
        printf("\n");
        
        player_turn(dice, roll_limit, player_used_categories, player_scores); // Player's turn
        computer_turn(dice, roll_limit, computer_used_categories, computer_scores); // Computer's turn
    }

    game_over = 1; // After all rounds are complete, set game_over to true

    display_score_table(player_scores, computer_scores, game_over); // Display the final score table with the total scores

    return 0;
}

/* Human player's turn */
void player_turn(int dice[], int roll_limit, int player_used_categories[], int player_scores[]) {
    printf("*** Player's turn ***\n");
    int roll_count = 0; // Resetting the number of rolls for each round
    const int YAHTZEE_INDEX = 12; 

    // Initial dice roll
    roll_dice(dice); // Roll all dice
    display_dice(dice); // Show the initial roll
        
    // Check if it's a Yahtzee immediately after the first roll
    if (score_yahtzee(dice) == YAHTZEE_SCORE) {
        printf("You scored a Yahtzee!\n");
        
        // Check if it's the first Yahtzee or a subsequent one
        if (player_used_categories[YAHTZEE_INDEX] == 1) {
            // Handle multiple Yahtzees (awarding bonus points or joker)
            player_handle_multiple_yahtzees(dice, player_used_categories, player_scores);
        } else {
            // First Yahtzee: score it normally and mark the category as used
            player_scores[YAHTZEE_INDEX] = YAHTZEE_SCORE;
            player_used_categories[YAHTZEE_INDEX] = 1;
            printf("Scored 50 points in the Yahtzee category.\n");
        }
        return; // End the turn immediately if Yahtzee is scored
    }

    // Loop until the player reaches the maximum rolls allowed
    while (1) {
        // Handle multiple Yahtzees before player chooses scoring category
        player_handle_multiple_yahtzees(dice, player_used_categories, player_scores);

        if (roll_count < roll_limit - 1) {
        // Prompt the user to choose to re-roll or choose a scoring category
            int choice;
            printf("Choose an option >>> \n");
            printf("1. Re-roll\n");
            printf("2. Choose scoring category\n");
            printf("\n");
            printf("Enter your choice (1 or 2): ");
            scanf("%d", &choice);
            printf("\n");

            if (choice == 1) {
                if (roll_count < roll_limit - 1) { // Check if re-rolls are still allowed
                    int rolls_left = roll_limit - roll_count; // Calculate remaining rolls
                    keep_dice(dice, rolls_left); // Ask the player which dice to keep or re-roll
                    roll_count++; // Increment roll count after each roll

                    // Check again if it's a Yahtzee after re-rolling
                    if (score_yahtzee(dice) == YAHTZEE_SCORE) {
                        printf("You scored a Yahtzee!\n");
                        
                         // Check for multiple Yahtzees
                        if (player_used_categories[YAHTZEE_INDEX] == 1) {
                            // Handle multiple Yahtzees (awarding bonus points or joker)
                            player_handle_multiple_yahtzees(dice, player_used_categories, player_scores);
                        } else {
                            // First Yahtzee: score it normally and mark the category as used
                            player_scores[YAHTZEE_INDEX] = YAHTZEE_SCORE;
                            player_used_categories[YAHTZEE_INDEX] = 1;
                            printf("Scored 50 points in the Yahtzee category.\n");
                        }
                        break; // End the turn if Yahtzee is scored after re-rolling
                    }
                }
            }
            else if (choice == 2) {
                player_choose_scoring_category(dice, player_used_categories, player_scores);
                break; // Exit the loop after scoring
            }
            else {
                printf("Invalid choice! Please enter 1 or 2.\n");
                continue; // Continue loop until a valid input has entered
            }
        }
        else {
            // Only allow scoring category selection if maximum rolls are exceeded
            printf("You have reached the maximum number of rolls for this turn.\n\n");
            player_choose_scoring_category(dice, player_used_categories, player_scores);
            break; // Exit the loop after scoring
        }
    }
}

/* Computer AI's turn */
void computer_turn(int dice[], int roll_limit, int computer_used_categories[], int computer_scores[]) {
    printf("*** Computer's turn ***\n");

    int roll_count = 0; // Reset the roll count for the computer's turn

    roll_dice(dice); // Initial roll
    display_dice(dice);
    
    while (roll_count < roll_limit - 1) {
        roll_count++;
        
        int reroll[NUM_OF_DICE] = {1, 1, 1, 1, 1}; // Initially set all to reroll

        // Decision-making for keeping or rerolling dice
        decide_dice_to_reroll(dice, reroll);

        // Reroll selected dice
        for (int i = 0; i < NUM_OF_DICE; i++) {
            if (reroll[i] == 1) { // Check if the die is marked for re-rolling
                dice[i] = rand() % 6 + 1; // Reroll it
            }
        }
        display_dice(dice);
    }

    computer_choose_scoring_category(dice, computer_scores, computer_used_categories);
}

void decide_dice_to_reroll(int dice[], int reroll[]) {
    int counts[7] = {0}; // Index 0 will not be used

    // Count occurrences of each die value (1 to 6)
    for (int i = 0; i < NUM_OF_DICE; i++) {
        counts[dice[i]]++;
    }

    // Assume all dice will be rerolled
    for (int i = 0; i < NUM_OF_DICE; i++) {
        reroll[i] = 1; 
    }

    // Logic: Keep if there are 3 or more of the same dice value, else reroll all
    for (int value = 1; value <= 6; value++) {
        if (counts[value] >= 3) {
            // Keep the dice of this value
            for (int i = 0; i < NUM_OF_DICE; i++) {
                if (dice[i] == value) {
                    reroll[i] = 0; // Don't re-roll
                }
            }
            break; // Only keep dice of one good value for now
        }
    }
}

void computer_choose_scoring_category(int dice[], int computer_scores[], int computer_used_categories[]) {
    int best_choice = -1;
    int best_score = -1;

    // Evaluate each category
    for (int category = 0; category < NUM_OF_SCORING_CATEGORIES; category++) {
        if (computer_used_categories[category] == 0) { // Check if not already used
            int score = score_based_on_categories(category + 1, dice); // Score function assumes 1-based category index
            if (score > best_score) {
                best_score = score;
                best_choice = category; // Track the best category
            }
        }
    }

    // Record the best choice
    if (best_choice != -1) {
        computer_scores[best_choice] = best_score; // Assign score to the category
        computer_used_categories[best_choice] = 1; // Mark as used
        printf("Computer chose category %d and scored %d points.\n", best_choice + 1, best_score);
    } else {
        printf("Computer has no scoring options left.\n");
    }
}

/* Rolling 5 dice*/
void roll_dice(int dice[]) {
    for (int i = 0; i < NUM_OF_DICE; i++) {
        dice[i] = rand() % 6 + 1; // Generating a random number between 1 and 6
    }
}

/* Choosing the dice to keep or re-roll */
void keep_dice(int dice[], int rolls_left) {
    int keep[NUM_OF_DICE]; // Keeping dice are marked as 1 while rerolling dice are marked 0

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
    printf("\n");
    
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
    printf("Roll result: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dice[i]); // Print each die's value
    }
    printf("\n\n"); // New line after printing all dice
}

/* Allow Player to choose a scoring catagory */
void player_choose_scoring_category(int dice[], int player_used_categories[], int player_scores[]) {
    int choice;
    
    printf("Choose a scoring category:\n");
    printf("--------------------------\n");

    for (int i = 0; i < NUM_OF_SCORING_CATEGORIES; i++) {
        if (player_used_categories[i] == 0) {
            switch (i + 1) {
            case 1: printf("1.  Ones\n"); 
                break;
            case 2: printf("2.  Twos\n"); 
                break;
            case 3: printf("3.  Threes\n"); 
                break;
            case 4: printf("4.  Fours\n"); 
                break;
            case 5: printf("5.  Fives\n"); 
                break;
            case 6: printf("6.  Sixes\n"); 
                break;
            case 7: printf("7.  Three of a Kind\n"); 
                break;
            case 8: printf("8.  Four of a Kind\n"); 
                break;
            case 9: printf("9.  Full House\n"); 
                break;
            case 10: printf("10. Small Straight\n"); 
                break;
            case 11: printf("11. Large Straight\n"); 
                break;
            case 12: printf("12. Chance\n"); 
                break;
            case 13: printf("13. YAHTZEE\n"); 
                break;
            default: 
                break;
            }
        }
    }
    printf("--------------------------\n");

    int valid_choice = 0; // Flag to check if choice is valid
    while (!valid_choice) {
        printf("Choice: ");
        scanf("%d", &choice); // Get the user's choice

        // Check if the input is valid (between 1 and 13)
        if (choice >= 1 && choice <= NUM_OF_SCORING_CATEGORIES
    ) {
            // Check if the category has already been used
            if (player_used_categories[choice - 1] == 0) {
                valid_choice = 1; // Input is valid
            }
            else {
                printf("You have already scored in this category! Choose another category.\n\n");
            }
        }
        else {
            printf("Invalid choice! Please choose a category between 1 and 13.\n");
        }
    }

    int score = score_based_on_categories(choice, dice);
    if (score == 0) {
        printf("Invalid input.\n");
    }

    player_scores[choice - 1] = score; // Store the score for the chosen category
    player_used_categories[choice - 1] = 1; // Mark the category as used
    
    printf("%d points scored.\n", score); // Display the score
}

int score_based_on_categories(int choice, int dice[]) {
    int score = 0; // Initialize score variable

    // Determine the score based on the chosen category
    switch (choice) {
        case 1:
            return score_single_numbers(dice, 1);
        case 2:
            return score_single_numbers(dice, 2);
        case 3:
            return score_single_numbers(dice, 3);
        case 4:
            return score_single_numbers(dice, 4);
        case 5:
            return score_single_numbers(dice, 5);
        case 6:
            return score_single_numbers(dice, 6);
        case 7:
            return score_three_of_a_kind(dice);
        case 8:
            return score_four_of_a_kind(dice);
        case 9:
            return score_full_house(dice);
        case 10:
            return score_small_straight(dice);
        case 11:
            return score_large_straight(dice);
        case 12:
            return score_chance(dice);
        case 13:
            return score_yahtzee(dice);
        default:
            return 0;
    }
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
        return FULL_HOUSE_POINTS;  // Return 25 points for a Full House
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
        return SMALL_STRAIGHT_POINTS; // Return 30 points for a small straight
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
        return LARGE_STRAIGHT_POINTS; // Return 40 points for a large straight
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
            return YAHTZEE_SCORE; // Return 50 points for a Yahtzee
        }
    }
    return 0; // Returning 0 if no Yahtzee found.
}

void player_handle_multiple_yahtzees(int dice[], int player_used_categories[], int player_scores[]) {
    int yahtzee_value = dice[0];  // All dice are the same in a Yahtzee
    const int YAHTZEE_INDEX = 12;
    int yahtzee_score = score_yahtzee(dice);

    if (yahtzee_score == 50) {
        // Check if the Yahtzee has already been scored
        if (player_used_categories[YAHTZEE_INDEX] == 1) {  // Yahtzee category already filled
            if (player_scores[YAHTZEE_INDEX] > 0) {  // Scored a Yahtzee before
                printf("Congratulations! You rolled another Yahtzee and earned a joker!\n");
                // Add 100 bonus points to the Yahtzee category
                player_scores[YAHTZEE_INDEX] += MULTI_YAHTZEE_BONUS;
                printf("100 bonus points awarded.\n");
            } else {
                printf("You have already put 0 in the Yahtzee box.\n");
            }
            // Regardless of whether a bonus was awarded, the joker is triggered
            printf("You received a joker!\n");
            joker(dice, player_used_categories, player_scores, yahtzee_value);
        } else {
            // First Yahtzee scored
            printf("You scored a Yahtzee!\n");
            player_scores[YAHTZEE_INDEX] = yahtzee_score;  // Set the score for Yahtzee category
            player_used_categories[YAHTZEE_INDEX] = 1;  // Mark the category as used
            printf("Scored %d points in the Yahtzee category.\n", yahtzee_score);
        }
    }
}


void joker(int dice[], int used_categories[], int scores[], int yahtzee_value) {
    // Check if the corresponding upper section category is unscored
    if (used_categories[yahtzee_value - 1] == 0) {
    // If the upper section(1 to 6) for the Yahtzee value is unscored, score it
    int score = score_single_numbers(dice, yahtzee_value);
    scores[yahtzee_value - 1] = score;
    used_categories[yahtzee_value - 1] = 1;
    printf("Scored %d points in the %d's category.\n", score, yahtzee_value);
    }

    else {
        // Otherwise, player can score in any lower section (joker rule)
        printf("You may now score in any other lower section category.\n");
        // Prompt player to choose a lower section category
        player_choose_lower_category(dice, used_categories, scores);
    }
}

/* A sub function for the joker function .*/
void player_choose_lower_category(int dice[], int player_used_categories[], int player_scores[]) {
    int choice;
    const int NUM_OF_LOWER_SCORING_CATAGORIES = 6;

    for (int i = 0; i < NUM_OF_LOWER_SCORING_CATAGORIES; i++) {
        if (player_used_categories[i + 6] == 0) {
            switch (i + 7) {
                case 7: printf("7.  Three of a Kind\n"); 
                    break;
                case 8: printf("8.  Four of a Kind\n"); 
                    break;
                case 9: printf("9.  Full House\n"); 
                    break;
                case 10: printf("10. Small Straight\n"); 
                    break;
                case 11: printf("11. Large Straight\n"); 
                    break;
                case 12: printf("12. Chance\n"); 
                    break;
                case 13: printf("13. YAHTZEE\n"); 
                    break;
                default: 
                    break;
            }
        }
    }

    int valid_choice = 0;
    while (!valid_choice) {
        printf("Choice: ");
        scanf("%d", &choice);

        // Ensure the choice is in the lower section and hasn't been scored yet
        if (choice >= 7 && choice <= 12 && player_used_categories[choice - 1] == 0) {
            valid_choice = 1;
        } else {
            printf("Invalid choice or category already scored. Please try again.\n");
        }
    }

    // Score the chosen lower section
    int score = 0;
    // Note: Yahtzee is a superset of 3 of a kind, 4 of a kind, full house and chance,
    //       but you can also choose small or large straight and will get the normal 30 and 40 points for those.
    switch (choice) {
        case 7: score = score_three_of_a_kind(dice); 
            break;
        case 8: score = score_four_of_a_kind(dice);
            break;
        case 9: score = score_full_house(dice);
            break;
        case 10: score = SMALL_STRAIGHT_POINTS; // Full points for Small Straight
            break;
        case 11: score = LARGE_STRAIGHT_POINTS; // Full points for Large Straight
            break;
        case 12: score = score_chance(dice);
            break;
    }
    player_scores[choice - 1] = score; // Record the score
    player_used_categories[choice - 1] = 1; // Mark the category as used
    printf("%d points scored in the chosen category.\n", score);
}

/* Display the score table */
void display_score_table(int player_scores[], int computer_scores[], int game_over) {

    int player_singles_sum = calc_score_of_singles(player_scores); // Calculate the sum of single scores (1 to 6) of the player
    int player_bonus = check_bonus(player_scores); // Check whether the player is eligible for a bonus or not

    int computer_singles_sum = calc_score_of_singles(computer_scores); // Calculate the sum of single scores (1 to 6) of the computer
    int computer_bonus = check_bonus(computer_scores); // Check whether the computer is eligible for a bonus or not

    char player_score_str[10];   // Buffer for player scores
    char computer_score_str[10]; // Buffer for computer scores

    // Check if all singles have been scored
    int player_singles_scored = all_singles_scored(player_scores);
    int computer_singles_scored = all_singles_scored(computer_scores);

    // Printing the score table
    printf("\n***************** YAHTZEE SCORE TABLE *****************\n");
    printf("-------------------------------------------------------\n");
    printf("| Category         |  Player Score  |  Computer Score |\n");
    printf("-------------------------------------------------------\n");
    printf("| Ones (1s)        | %-14s | %-15s |\n", convert_score_to_str(player_scores[0], player_score_str), convert_score_to_str(computer_scores[0], player_score_str));
    printf("| Twos (2s)        | %-14s | %-15s |\n", convert_score_to_str(player_scores[1], player_score_str), convert_score_to_str(computer_scores[1], player_score_str));
    printf("| Threes (3s)      | %-14s | %-15s |\n", convert_score_to_str(player_scores[2], player_score_str), convert_score_to_str(computer_scores[2], player_score_str));
    printf("| Fours (4s)       | %-14s | %-15s |\n", convert_score_to_str(player_scores[3], player_score_str), convert_score_to_str(computer_scores[3], player_score_str));
    printf("| Fives (5s)       | %-14s | %-15s |\n", convert_score_to_str(player_scores[4], player_score_str), convert_score_to_str(computer_scores[4], player_score_str));
    printf("| Sixes (6s)       | %-14s | %-15s |\n", convert_score_to_str(player_scores[5], player_score_str), convert_score_to_str(computer_scores[5], player_score_str));
    printf("-------------------------------------------------------\n");

    // Display singles sum and bonus only if all singles have been scored
    if (player_singles_scored) {
        printf("| Sum              | %-14s | %-15s |\n", convert_score_to_str(player_singles_sum, player_score_str), convert_score_to_str(computer_singles_sum, computer_score_str));
        printf("| Bonus            | %-14s | %-15s |\n", convert_score_to_str(player_bonus, player_score_str), convert_score_to_str(computer_bonus, computer_score_str));
    }
    else {
        printf("| Sum              | %-14s | %-15s |\n", " ", " "); // Blank if not all singles are scored
        printf("| Bonus            | %-14s | %-15s |\n", " ", " "); // Blank if not all singles are scored
    }

    printf("-------------------------------------------------------\n");
    printf("| Three of a Kind  | %-14s | %-15s |\n", convert_score_to_str(player_scores[6], player_score_str), convert_score_to_str(computer_scores[6], computer_score_str));
    printf("| Four of a Kind   | %-14s | %-15s |\n", convert_score_to_str(player_scores[7], player_score_str), convert_score_to_str(computer_scores[7], computer_score_str));
    printf("| Full House       | %-14s | %-15s |\n", convert_score_to_str(player_scores[8], player_score_str), convert_score_to_str(computer_scores[8], computer_score_str));
    printf("| Small Straight   | %-14s | %-15s |\n", convert_score_to_str(player_scores[9], player_score_str), convert_score_to_str(computer_scores[9], computer_score_str));
    printf("| Large Straight   | %-14s | %-15s |\n", convert_score_to_str(player_scores[10], player_score_str), convert_score_to_str(computer_scores[10], computer_score_str));
    printf("| Chance           | %-14s | %-15s |\n", convert_score_to_str(player_scores[11], player_score_str), convert_score_to_str(computer_scores[11], computer_score_str));
    printf("| Yahtzee          | %-14s | %-15s |\n", convert_score_to_str(player_scores[12], player_score_str), convert_score_to_str(computer_scores[12], computer_score_str));
    printf("-------------------------------------------------------\n");

    // Display the total score only if the game is over
    if (game_over) {
        int player_total_score = calc_total_score(player_scores); // Calculate the total score of the player
        int computer_total_score = calc_total_score(computer_scores); // Calculate the total score of the computer
        printf("| Total Score      | %-14s | %-15s |\n", convert_score_to_str(player_total_score, player_score_str), convert_score_to_str(computer_total_score, computer_score_str));
    }
    else {
        printf("| Total Score      | %-14s | %-15s |\n", " ", " "); // Display blank spaces for the total_score if the game isn't over
    }

    printf("-------------------------------------------------------\n");
    printf("\n");
}

/* Making the score in a scoring category display a blank space until user scores in that category */
char* convert_score_to_str(int score, char *score_str) {
        if (score == -1) {
            return " "; // Return a space if no score in that category yet
        }
        else {
            sprintf(score_str, "%d", score); // Convert score to string
            return score_str; // Return the score as a string
        }
    }

/* Calculate the sum of scores of singles (1 to 6) */
int calc_score_of_singles(int scores[]) {
    int singles_sum = 0;
    for (int i = 0; i < 6; i++) {
        if (scores[i] >= 0) {
            singles_sum += scores[i];
        }
    }
    return singles_sum; // Returning the sum of the scores of singles
}

/* Calculate the total score including the bonus for singles */
int calc_total_score(int scores[]) {
    int total_score = 0;

    // Sum scores for all categories
    for (int i = 0; i < NUM_OF_SCORING_CATEGORIES; i++) {
        if (scores[i] >= 0) {
            total_score += scores[i];
        }
    }

    int bonus = check_bonus(scores); // Checking for a bonus
    if (bonus) {
        total_score += bonus;
    }

    return total_score; // Returning the total score
}

/* Check if the player has won bonus points */
int check_bonus(int scores[]) {
    int bonus;
    int singles_sum = calc_score_of_singles(scores); // Get the sum of the scores of singles (1 to 6)
    if (singles_sum >= BONUS_POINTS_THRESHOLD) {  // Checking if the player is eligible for a bonus
            bonus = BONUS;
    }
    else {
        bonus = 0; // If not eligible for a bonus initailizing bonus to 0
    }
    return bonus; // Returning bonus
}

int all_singles_scored(int scores[]) {
    for (int i = 0; i < 6; i++) { // Check indices 0 to 5 for ones to sixes
        if (scores[i] == -1) {
            return 0; // Return 0 if any single category is unscored
        } 
    }
    return 1; // Return 1 if all singles are scored
}