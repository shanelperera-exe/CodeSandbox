#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Defining constants
#define NUM_OF_DICE 5
#define NUM_OF_SCORING_CATEGORIES 13
#define ROLL_LIMIT 3
#define FULL_HOUSE_POINTS 25
#define SMALL_STRAIGHT_POINTS 30
#define LARGE_STRAIGHT_POINTS 40
#define BONUS_POINTS_THRESHOLD 63
#define BONUS 35
#define YAHTZEE_SCORE 50
#define MULTI_YAHTZEE_BONUS 100
#define FOURS 3
#define FIVES 4
#define SIXES 5
#define THREE_OF_A_KIND 6
#define FOUR_OF_A_KIND 7
#define FULL_HOUSE 8
#define SMALL_STRAIGHT 9
#define LARGE_STRAIGHT 10
#define CHANCE 11
#define YAHTZEE 12

/* Function declarations */
void game();
void roll_dice(int dice[]);
void keep_dice(int dice[], int rolls_left);
void display_dice(int dice[]);
int score_based_on_categories(int choice, int dice[]);
void player_choose_scoring_category(int dice[], int player_used_categories[], int player_scores[]);
int computer_choose_scoring_category(int dice[], int computer_scores[], int computer_used_categories[], int roll_count);
void display_score_table(int player_scores[], int computer_scores[], int game_over);
int calc_score_of_singles(int scores[]);
int check_bonus(int scores[]);
int calc_total_score(int scores[]);
void player_turn(int dice[], int player_used_categories[], int player_scores[]);
void computer_turn(int dice[], int computer_used_categories[], int computer_scores[]);
void decide_dice_to_reroll(int dice[], int reroll[], int computer_used_categories[], int roll_count);
char* convert_score_to_str(int score, char *score_str);
int all_singles_scored(int scores[]);
void display_winner(int player_scores[], int computer_scores[]);
void logo(void);
void game(void);
int main_menu(void);
void display_rules(void);
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
    logo();
    printf("\n***** Welcome to Yahtzee! *****\n\n");
    main_menu();

    return 0;
}

void game(void) {
    int dice[NUM_OF_DICE];
    int roll_count; // Counter for the number of rolls
    int player_scores[NUM_OF_SCORING_CATEGORIES] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Array to store human player scores for each category
    int player_used_categories[NUM_OF_SCORING_CATEGORIES] = {0}; // Array to track used categories by the player
    int computer_used_categories[NUM_OF_SCORING_CATEGORIES] = {0}; // Array to track used categories by the player
    int computer_scores[NUM_OF_SCORING_CATEGORIES] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Array to store computer AI scores for each category
    // Initialize scores to -1 to hide categories until a score is recorded; 0 will display only once 0 is stored.
    
    srand(time(NULL)); // Seed the random number generator using current time

    int game_over = 0; // Flag to check if the game has ended (Initializing game_over to false)

    for (int round = 0; round < NUM_OF_SCORING_CATEGORIES; round++) {
        display_score_table(player_scores, computer_scores, game_over); // Display the score table at the beginning of the each round
        printf("*** ROUND %d ***\n", round + 1); // Displaying round number
        printf("\n");
        
        player_turn(dice, player_used_categories, player_scores); // Player's turn
        computer_turn(dice, computer_used_categories, computer_scores); // Computer's turn
    }

    game_over = 1; // After all rounds are complete, set game_over to true

    display_score_table(player_scores, computer_scores, game_over); // Display the final score table with the total scores

    display_winner(player_scores, computer_scores);
}

/* Human player's turn */
void player_turn(int dice[], int player_used_categories[], int player_scores[]) {
    printf("*** Player's turn ***\n");
    int roll_count = 0; // Resetting the number of rolls for each round 

    // Initial dice roll
    roll_dice(dice); // Roll all dice
    roll_count++;
    display_dice(dice); // Show the initial roll
        
    // Check if it's a Yahtzee immediately after the first roll
    if (score_yahtzee(dice) == YAHTZEE) {
        printf("You scored a Yahtzee!\n");
        
        // Check if it's the first Yahtzee or a subsequent one
        if (player_used_categories[YAHTZEE] == 1) {
            // Handle multiple Yahtzees (awarding bonus points or joker)
            player_handle_multiple_yahtzees(dice, player_used_categories, player_scores);
        } else {
            // First Yahtzee: score it normally and mark the category as used
            player_scores[YAHTZEE] = YAHTZEE_SCORE;
            player_used_categories[YAHTZEE] = 1;
            printf("Scored 50 points in the Yahtzee category.\n");
        }
        return; // End the turn immediately if Yahtzee is scored
    }

    // Loop until the player reaches the maximum rolls allowed
    while (1) {
        // Handle multiple Yahtzees before player chooses scoring category
        player_handle_multiple_yahtzees(dice, player_used_categories, player_scores);

        if (roll_count < ROLL_LIMIT) {
        // Prompt the user to choose to re-roll or choose a scoring category
            char choice;
            printf("Choose an option >>> \n");
            printf("[R] Re-roll\n");
            printf("[C] Choose scoring category\n");
            printf("\n");
            printf("Enter your choice [R] or [C]: ");
            scanf(" %c", &choice);
            printf("\n");

            if (choice == 'r' || choice == 'R') {
                if (roll_count < ROLL_LIMIT) { // Check if re-rolls are still allowed
                    int rolls_left = ROLL_LIMIT - roll_count; // Calculate remaining rolls
                    keep_dice(dice, rolls_left); // Ask the player which dice to keep or re-roll
                    roll_count++; // Increment roll count after each roll

                    // Check again if it's a Yahtzee after re-rolling
                    if (score_yahtzee(dice) == YAHTZEE_SCORE) {
                        printf("You scored a Yahtzee!\n");
                        
                         // Check for multiple Yahtzees
                        if (player_used_categories[YAHTZEE] == 1) {
                            // Handle multiple Yahtzees (awarding bonus points or joker)
                            player_handle_multiple_yahtzees(dice, player_used_categories, player_scores);
                        } else {
                            // First Yahtzee: score it normally and mark the category as used
                            player_scores[YAHTZEE] = YAHTZEE_SCORE;
                            player_used_categories[YAHTZEE] = 1;
                            printf("Scored 50 points in the Yahtzee category.\n");
                        }
                        break; // End the turn if Yahtzee is scored after re-rolling
                    }
                }
            }
            else if (choice == 'c' || choice == 'C') {
                player_choose_scoring_category(dice, player_used_categories, player_scores);
                break; // Exit the loop after scoring
            }
            else {
                printf("Invalid choice! Please enter 'R' or 'C'.\n");
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
void computer_turn(int dice[], int computer_used_categories[], int computer_scores[]) {
    printf("*** Computer's turn ***\n");

    int roll_count = 0; // Reset the roll count for the computer's turn
    int scored = 0;     // Variable to track if the computer has scored

    roll_dice(dice); // Initial roll
    roll_count++;
    display_dice(dice);

    // Check for a scoring opportunity after the first roll (but don't force scoring unless it's a great option)
    scored = computer_choose_scoring_category(dice, computer_scores, computer_used_categories, roll_count);

    // Only score if there's a strong reason to end the turn (like a Yahtzee or Large Straight)
    if (scored) {
        printf("Computer has found a strong scoring option after the first roll.\n");
        return; // End the turn if scored
    }

    // If the computer didn't score, continue with rerolls
    while (roll_count < ROLL_LIMIT) {
        int reroll[NUM_OF_DICE] = {1, 1, 1, 1, 1}; // Initially set all dice to reroll

        // Decide which dice to reroll based on the current strategy
        decide_dice_to_reroll(dice, reroll, computer_used_categories, roll_count);

        // Perform the reroll
        for (int i = 0; i < NUM_OF_DICE; i++) {
            if (reroll[i] == 1) { // Reroll only marked dice
                dice[i] = rand() % 6 + 1;
            }
        }
        display_dice(dice);

        // Check again after each reroll
        scored = computer_choose_scoring_category(dice, computer_scores, computer_used_categories, roll_count);
        if (scored) {
            printf("Computer has scored after rerolls, ending turn.\n");
            return; // End the turn after scoring
        }
       
        roll_count++;
    }

    // After all rolls are used, if no scoring was made, choose the best option left
    if (!scored) {
        computer_choose_scoring_category(dice, computer_scores, computer_used_categories, roll_count);
    } else {
        printf("Computer had no scoring opportunities this turn.\n");
    }
}


void decide_dice_to_reroll(int dice[], int reroll[], int computer_used_categories[], int roll_count) {
    int counts[7] = {0}; // Index 0 will not be used

    // Count occurrences of each die value (1 to 6)
    for (int i = 0; i < NUM_OF_DICE; i++) {
        counts[dice[i]]++;
    }

    // Assume all dice will be rerolled initially
    for (int i = 0; i < NUM_OF_DICE; i++) {
        reroll[i] = 1;
    }

    // 1. Prioritize keeping all 6's, 5's, or 4's if going for high scores in the upper section
    for (int value = 6; value >= 4; value--) {
        if (counts[value] >= 3) {
            for (int i = 0; i < NUM_OF_DICE; i++) {
                if (dice[i] == value) {
                    reroll[i] = 0; // Keep all 6's, 5's, or 4's
                }
            }
        }
    }

    // 2. If the upper section categories for these high values are not yet filled, aim for them
    for (int value = 6; value >= 1; value--) {
        if (computer_used_categories[value - 1] == 0 && counts[value] >= 2) { // Favor filling upper section categories
            for (int i = 0; i < NUM_OF_DICE; i++) {
                if (dice[i] == value) {
                    reroll[i] = 0; // Keep dice of that value
                }
            }
        }
    }

    // 3. Check for possible straights
    // Large straight (1, 2, 3, 4, 5 or 2, 3, 4, 5, 6)
    if ((counts[1] && counts[2] && counts[3] && counts[4] && counts[5]) ||
        (counts[2] && counts[3] && counts[4] && counts[5] && counts[6])) {
        for (int i = 0; i < NUM_OF_DICE; i++) {
            if (dice[i] == 1 || dice[i] == 2 || dice[i] == 3 || dice[i] == 4 || dice[i] == 5 || dice[i] == 6) {
                reroll[i] = 0; // Keep 1, 2, 3, 4, 5 or 2, 3, 4, 5, 6 for large straight
            }
        }
    }

    // Small straight (1, 2, 3, 4 or 2, 3, 4, 5 or 3, 4, 5, 6)
    if ((counts[1] && counts[2] && counts[3] && counts[4]) || 
        (counts[2] && counts[3] && counts[4] && counts[5]) || 
        (counts[3] && counts[4] && counts[5] && counts[6])) {
        for (int i = 0; i < NUM_OF_DICE; i++) {
            if (dice[i] == 1 || dice[i] == 2 || dice[i] == 3 || dice[i] == 4 || dice[i] == 5 || dice[i] == 6) {
                reroll[i] = 0; // Keep the numbers for small straight
            }
        }
        return; // Large straight already achieved, exit early
    }

    // reroll lower values and keep higher values
    int decision_made = 0;
    if (roll_count < ROLL_LIMIT) {
        for (int high_value = 6; high_value >= 3; high_value--) {
            for (int low_value = high_value - 1; low_value >= 1; low_value--) {
                if (counts[high_value] >= 2 && counts[low_value] >= 2) {
                    for (int i = 0; i < NUM_OF_DICE; i++) {
                        if (dice[i] == high_value) {
                            reroll[i] = 0; // Keep higher value dice
                        } else if (dice[i] == low_value) {
                            reroll[i] = 1; // Reroll lower value dice
                        }
                    }
                    decision_made = 0;
                    break; // Exit after making this decision
                }
            }
            if (decision_made) break;
        }
    }
    
    // 4. Keep 3 or more of a kind (for Yahtzee, Full House, 4 of a Kind)
    for (int value = 6; value >= 1; value--) { // Start from 6 to prioritize higher numbers
        if (counts[value] >= 3) {
            // Keep the dice of this value
            for (int i = 0; i < NUM_OF_DICE; i++) {
                if (dice[i] == value) {
                    reroll[i] = 0; // Don't re-roll
                }
            }
            break; // Keep dice of one strong value for now
        }
    }

    // Keep any high dice (3, 4, 5, 6) for Chance
    if (computer_used_categories[CHANCE] == 0) {
        for (int i = 0; i < NUM_OF_DICE; i++) {
            if (dice[i] >= 3) {
                reroll[i] = 0; // Keep high dice for Chance
            }
        }
    }
}

int computer_choose_scoring_category(int dice[], int computer_scores[], int computer_used_categories[], int roll_count) {
    int best_choice = -1;  // Initialize the best choice of category
    int best_score = -1;   // Highest score the computer can get in any unscored category
    int counts[7] = {0};   // Count occurrences of each dice value (1 to 6)

    // Count occurrences of each die value
    for (int i = 0; i < NUM_OF_DICE; i++) {
        counts[dice[i]]++; // Increment the count for each die value
    }

    // If this is the first roll, only consider very strong categories
    if (roll_count < ROLL_LIMIT) {
        // 1. Check for Yahtzee (if all dice are the same)
        if (computer_used_categories[YAHTZEE] == 0) {
            int score = score_yahtzee(dice);
            if (score > best_score) {
                best_choice = YAHTZEE;
                best_score = score;
            }
        }

        // 2. Check for Large Straight first
        if (computer_used_categories[LARGE_STRAIGHT] == 0) {
            int score = score_large_straight(dice);
            if (score > best_score) {
                best_choice = LARGE_STRAIGHT;
                best_score = score;
            }
        }

        // 3. Check for Four of a Kind with high values (e.g., 4 6's or 5's)
        if (computer_used_categories[FOUR_OF_A_KIND] == 0 && (counts[6] >= 4 || counts[5] >= 4)) {
            int score = score_four_of_a_kind(dice);
            if (score > best_score) {
                best_choice = FOUR_OF_A_KIND;
                best_score = score;
            }
        }

        // 4. Check for Upper Section during the first roll, but only for high values (6's, 5's, optionally 4's)
        for (int i = 6; i >= 4; i--) { // Only consider 6's, 5's, and 4's
            if (computer_used_categories[i - 1] == 0 && counts[i] >= 4) { // If unscored and 3 or more dice
                int score = score_single_numbers(dice, i); // Calculate the score for this number
                if (score > best_score) { // If it's the best score found so far
                    best_choice = i - 1;  // Choose this category
                    best_score = score;
                }
            }
        }

        // 4. Check for Full House on the first roll unless there are three 6's or 5's
        if (roll_count == 1 && computer_used_categories[FULL_HOUSE] == 0) {
            int score = score_full_house(dice);
            if (score > best_score && !(counts[6] == 3 || counts[5] == 3)) {
                best_choice = FULL_HOUSE;
                best_score = score;
            }
        }

        // If no strong options are found, return 0 to indicate no scoring yet
        if (best_choice != -1 && best_score > 0) {
            computer_scores[best_choice] = best_score; // Update score
            computer_used_categories[best_choice] = 1; // Mark category as used
            printf("Computer chose category %d and scored %d points.\n", best_choice + 1, best_score);
            return 1; // Indicate that the computer has scored
        }

        // If no strong categories were found, return 0 to allow rerolls
        return 0;
    }

    // Prioritize Upper Section if a high occurrence of a number or aiming for the bonus
    int upper_section_score = 0; // Variable to store potential upper section score
    int upper_section_choice = -1; // Variable to store the chosen upper section category

    // Check the upper section categories first, starting from the highest value (6's, then 5's, etc.)
    for (int i = 6; i >= 1; i--) {
        if (computer_used_categories[i - 1] == 0 && counts[i] >= 3) { // If category is unscored and has 3 or more dice
            int score = score_single_numbers(dice, i); // Calculate the score for this number
            if (score > upper_section_score) { // If it's a better upper section score
                upper_section_score = score;
                upper_section_choice = i - 1; // Save the choice for later
            }
        }
    }

    // If there is a strong upper section option (3 or more occurrences of a number), prioritize it
    if (upper_section_choice != -1) {
        // Prioritize scoring in the upper section if the upper section bonus hasn't been reached
        if (calc_score_of_singles(computer_scores) < 63) {
            best_choice = upper_section_choice;
            best_score = upper_section_score;
        }
    }


    // 2. Check for Yahtzee (if all dice are the same)
    if (computer_used_categories[YAHTZEE] == 0) {
        int score = score_yahtzee(dice);
        if (score > best_score) {
            best_choice = YAHTZEE;
            best_score = score;
        }
    }

    // 3. Check for Large Straight
    if (computer_used_categories[LARGE_STRAIGHT] == 0) {
        int score = score_large_straight(dice);
        if (score > best_score) {
            best_choice = LARGE_STRAIGHT;
            best_score = score;
        }
    }

    // 4. Prioritize Upper Section if a high occurrence of a number
    for (int i = 6; i >= 1; i--) {  // Start from 6's, then 5's, and so on
        if (computer_used_categories[i - 1] == 0 && counts[i] > 3) { // If the category is unscored
            int score = score_single_numbers(dice, i); // Calculate the score for this number
            if (counts[i] >= 3 && score > best_score) {  // Prioritize 3 or more occurrences
                best_choice = i - 1;  // Choose the best upper section category
                best_score = score;
            }
        }
    }

    // 5. Check for Full House, unless there are three 6's or 5's
    if (computer_used_categories[FULL_HOUSE] == 0) {
        int score = score_full_house(dice);
        if (score > best_score && !(counts[6] == 3 || counts[5] == 3)) {
            best_choice = FULL_HOUSE;
            best_score = score;
        }
    }

    // 6. Check for Three of a Kind after the upper section is filled
    for (int i = 6; i >= 4; i--) { // Prioritize 6's, then 5's, then 4's
        if (computer_used_categories[THREE_OF_A_KIND] == 0 && counts[i] >= 3) {
            int score = score_three_of_a_kind(dice);
            if (score > best_score) {
                best_choice = THREE_OF_A_KIND;
                best_score = score;
            }
        }
    }

    // 7. Check for Chance if nothing else fits
    if (computer_used_categories[CHANCE] == 0) {
        int score = score_chance(dice);
        if (score > best_score) {
            best_choice = CHANCE;
            best_score = score;
        }
    }

    // 8. Fallback: Check for other categories
    for (int category = 0; category < NUM_OF_SCORING_CATEGORIES; category++) {
        if (computer_used_categories[category] == 0) {
            int score = score_based_on_categories(category + 1, dice);
            if (score > best_score) {
                best_score = score;
                best_choice = category;
            }
        }
    }

    // Apply the best category choice
    if (best_choice != -1 && best_score > 0) {
        computer_scores[best_choice] = best_score; // Update score
        computer_used_categories[best_choice] = 1; // Mark category as used
        printf("Computer chose category %d and scored %d points.\n", best_choice + 1, best_score);
        return 1; // Indicate that the computer has scored
    }

    return 0; // Indicate that no scoring opportunity was found

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
        printf("\n");

        // Check if the input is valid (between 1 and 13)
        if (choice >= 1 && choice <= NUM_OF_SCORING_CATEGORIES) {
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
    int yahtzee_score = score_yahtzee(dice);

    if (yahtzee_score == 50) {
        // Check if the Yahtzee has already been scored
        if (player_used_categories[YAHTZEE] == 1) {  // Yahtzee category already filled
            if (player_scores[YAHTZEE] > 0) {  // Scored a Yahtzee before
                printf("Congratulations! You rolled another Yahtzee and earned a joker!\n");
                // Add 100 bonus points to the Yahtzee category
                player_scores[YAHTZEE] += MULTI_YAHTZEE_BONUS;
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
            player_scores[YAHTZEE] = yahtzee_score;  // Set the score for Yahtzee category
            player_used_categories[YAHTZEE] = 1;  // Mark the category as used
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
                default: 
                    break;
            }
        }
    }

    int valid_choice = 0;
    while (!valid_choice) {
        printf("Choice: ");
        scanf("%d", &choice);
        printf("\n");

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
    printf("| Ones (1s)        | %-14s | %-15s |\n", convert_score_to_str(player_scores[0], player_score_str), convert_score_to_str(computer_scores[0], computer_score_str));
    printf("| Twos (2s)        | %-14s | %-15s |\n", convert_score_to_str(player_scores[1], player_score_str), convert_score_to_str(computer_scores[1], computer_score_str));
    printf("| Threes (3s)      | %-14s | %-15s |\n", convert_score_to_str(player_scores[2], player_score_str), convert_score_to_str(computer_scores[2], computer_score_str));
    printf("| Fours (4s)       | %-14s | %-15s |\n", convert_score_to_str(player_scores[3], player_score_str), convert_score_to_str(computer_scores[3], computer_score_str));
    printf("| Fives (5s)       | %-14s | %-15s |\n", convert_score_to_str(player_scores[4], player_score_str), convert_score_to_str(computer_scores[4], computer_score_str));
    printf("| Sixes (6s)       | %-14s | %-15s |\n", convert_score_to_str(player_scores[5], player_score_str), convert_score_to_str(computer_scores[5], computer_score_str));
    printf("-------------------------------------------------------\n");

    // Only print the "Sum" and "Bonus" when all singles have been scored for the player and computer
    if (player_singles_scored && computer_singles_scored) {
        printf("| Sum              | %-14s | %-15s |\n", convert_score_to_str(player_singles_sum, player_score_str), convert_score_to_str(computer_singles_sum, computer_score_str));
        printf("| Bonus            | %-14s | %-15s |\n", convert_score_to_str(player_bonus, player_score_str), convert_score_to_str(computer_bonus, computer_score_str));
    } else if (player_singles_scored) {
        printf("| Sum              | %-14s | %-15s |\n", convert_score_to_str(player_singles_sum, player_score_str), " "); // Print player sum but leave computer blank
        printf("| Bonus            | %-14s | %-15s |\n", convert_score_to_str(player_bonus, player_score_str), " "); // Print player bonus but leave computer blank
    } else if (computer_singles_scored) {
        printf("| Sum              | %-14s | %-15s |\n", " ", convert_score_to_str(computer_singles_sum, computer_score_str)); // Leave player blank but print computer sum
        printf("| Bonus            | %-14s | %-15s |\n", " ", convert_score_to_str(computer_bonus, computer_score_str)); // Leave player blank but print computer bonus
    } else {
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

void display_winner(int player_scores[], int computer_scores[]) {
    // Calculate total scores
    int player_total_score = calc_total_score(player_scores);
    int computer_total_score = calc_total_score(computer_scores);

    // Print final scores and determine the winner
    printf("\n  FINAL SCORES:\n");
    printf("----------------------\n");
    printf("Player Total Score: %d\n", player_total_score);
    printf("Computer Total Score: %d\n", computer_total_score);
    printf("----------------------\n");

    if (player_total_score > computer_total_score) {
        printf("Congratulations! You win!\n");
    } else if (player_total_score < computer_total_score) {
        printf("Computer wins! Better luck next time!\n");
    } else {
        printf("It's a tie! Well played!\n");
    }
}

void logo(void) {
    printf("\n\n");
    printf("                                                         _______      _______\n");
    printf("Y     Y   AAAA   H   H  TTTTT  ZZZZZ   EEEEE  EEEEE     |       |    |       |\n");
    printf(" Y   Y   A    A  H   H    T        Z   E      E         |   o   |    | o   o |\n");
    printf("  YYY    AAAAAA  HHHHH    T      ZZ    EEEEE  EEEEE     |       |    |       |\n");
    printf("   Y     A    A  H   H    T     Z      E      E         | o   o |    | o   o |\n");
    printf("   Y     A    A  H   H    T    ZZZZZ   EEEEE  EEEEE     |       |    |       |\n");
    printf("                                                        |_______|    |_______|\n");
}

int main_menu(void) {
    int choice;
    
    printf("*** MAIN MENU ***\n");
    printf("-----------------\n");
    printf("[1] Start Game\n");
    printf("[2] Yahtzee Rules\n");
    printf("[3] Exit\n");
    printf("-----------------\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            game();
            break;
        case 2:
            display_rules();
            break;
        case 3:
            exit(0);
            break;
    }

    return choice;
}

void display_rules(void) {
    printf("\n**** YAHTZEE RULES ****\n\n");
    printf("The objective of YAHTZEE is to get as many points as possible by rolling five dice and getting certain combinations of dice.\n\n");
    printf("+++ Gameplay +++\n\n");
    printf("In each turn a player may throw the dice up to three times.A player doesn't have to roll all five dice on the second and third throw of a round,\nhe may put as many dice as he wants to the side and only throw the ones that don't have the numbers he's trying to get.\nFor example, a player throws and gets 1,3,3,4,6. He decides he want to try for the large straight, 1,2,3,4,5.\nSo, he puts 1,3,4 to the side and only throws 3 and 6 again, hoping to get 2 and 5.\n\n");
    printf("In this game you click on the dice you want to keep. They will be moved down and will not be thrown the next time you press the 'Roll Dice' button.\nIf you decide after the second throw in a turn that you don't want to keep the same dice before the third throw then you can click them again \nand they will move back to the table and be thrown in the third throw.\n\n\n");
    printf("+++ Upper section combinations +++\n\n");
    printf("• Ones: Get as many ones as possible.\n• Twos: Get as many twos as possible.\n• Threes: Get as many threes as possible.\n• Fours: Get as many fours as possible.\n• Fives: Get as many fives as possible.\n• Sixes: Get as many sixes as possible.\n\n");
    printf("For the six combinations above the score for each of them is the sum of dice of the right kind. \nE.g. if you get 1,3,3,3,5 and you choose Threes you will get 3*3 = 9 points. The sum of all the above combinations is calculated and if it is 63 or more, \nthe player will get a bonus of 35 points.On average a player needs three of each to reach 63, but it is not required to get three of each exactly, \nit is perfectly OK to have five sixes, and zero ones for example, as long as the sum is 63 or more the bonus will be awarded.\n\n\n");
    printf("+++ Lower section combinations +++\n\n");
    printf("• Three of a kind: Get three dice with the same number. Points are the sum all dice (not just the three of a kind).\n");
    printf("• Four of a kind: Get four dice with the same number. Points are the sum all dice (not just the four of a kind).\n");
    printf("• Full house: Get three of a kind and a pair, e.g. 1,1,3,3,3 or 3,3,3,6,6. Scores 25 points.\n");
    printf("• Small straight: Get four sequential dice, 1,2,3,4 or 2,3,4,5 or 3,4,5,6. Scores 30 points.\n");
    printf("• Large straight: Get five sequential dice, 1,2,3,4,5 or 2,3,4,5,6. Scores 40 points.\n");
    printf("• Chance: You can put anything into chance, it's basically like a garbage can when you don't have anything else you can use the dice for. \n          The score is simply the sum of the dice.\n");
    printf("• YAHTZEE: Five of a kind. Scores 50 points. You can optionally get multiple Yahtzees, see below for details.\n\n\n");
    printf("+++ Multiple Yahtzees +++\n\n");
    printf("The rules around multiple Yahtzees are a bit complex. There are a couple of different cases:\n\n");
    printf("1. You already have a Yahtzee: You get a 100 bonus points in the Yahtzee box, but you also have a joker, which means that you can choose \n                               another move for the Yahtzee you just got. If the number you got yahtzees with has not been filled out in the upper section, \n                               then you must choose that. E.g. if you get an additional Yahtzee with 2's, and you haven't filled out the 2's in the upper section then \n                               you must choose that, and get 10 points for it. If the upper section box is already filled then you can choose any of the lower region boxes, \n                               and they will be scored as normal. Yahtzee is a superset of 3 of a kind, 4 of a kind, full house and chance, but you can also choose \n                               small or large straight and will get the normal 30 and 40 points for those.\n\n");
    printf("2. You've already put 0 in the Yahtzee box: In this case you get no 100 point bonus, but you do get a joker, and can choose your move following the rules \n                                            described above for jokers.\n\n\n");
    
    while (1) {
        char choice;
        printf("[B] Back to Main Menu\n");
        printf("[E] Exit\n");

        printf("\nChoose an option: ");
        scanf(" %c", &choice);
        printf("\n");

        if (choice == 'B' || choice == 'b') {
            main_menu();
        }
        else if (choice == 'E' || choice == 'e') {
            exit(0);
        }
        else {
            printf("Invalid Input.\n\n");
            continue;
        }   
    }
}