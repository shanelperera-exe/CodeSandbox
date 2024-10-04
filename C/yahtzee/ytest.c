#include <stdio.h>

#define NUM_CATEGORIES 13
#define BONUS_THRESHOLD 63
#define BONUS_POINTS 35

// Function declarations
void print_score_table(int player_scores[], int computer_scores[]);

int main(void) {
    int player_scores[NUM_CATEGORIES] = {0};  // Initialize player scores to 0 for all categories
    int computer_scores[NUM_CATEGORIES] = {0}; // Initialize computer scores to 0 for all categories

    // Example scores (update these based on game logic)
    player_scores[0] = 3;  // Aces
    player_scores[1] = 4;  // Twos
    player_scores[2] = 9;  // Threes
    player_scores[3] = 12; // Fours
    player_scores[4] = 10; // Fives
    player_scores[5] = 18; // Sixes
    player_scores[6] = 15; // Three of a Kind
    player_scores[7] = 20; // Four of a Kind
    player_scores[8] = 25; // Full House
    player_scores[9] = 30; // Small Straight
    player_scores[10] = 40; // Large Straight
    player_scores[11] = 50; // Yahtzee
    player_scores[12] = 18; // Chance

    // Example computer scores (update these based on game logic)
    computer_scores[0] = 5;  // Aces
    computer_scores[1] = 8;  // Twos
    computer_scores[2] = 6;  // Threes
    computer_scores[3] = 14; // Fours
    computer_scores[4] = 12; // Fives
    computer_scores[5] = 24; // Sixes
    computer_scores[6] = 12; // Three of a Kind
    computer_scores[7] = 16; // Four of a Kind
    computer_scores[8] = 25; // Full House
    computer_scores[9] = 30; // Small Straight
    computer_scores[10] = 40; // Large Straight
    computer_scores[11] = 50; // Yahtzee
    computer_scores[12] = 20; // Chance

    // Print the score table
    print_score_table(player_scores, computer_scores);
    
    return 0;
}

void print_score_table(int player_scores[], int computer_scores[]) {
    // Table header
    printf("Yahtzee Score Table:\n");
    printf("------------------------------------------------------------\n");
    printf("| Category          | Player Score    | Computer Score   |\n");
    printf("------------------------------------------------------------\n");
    
    // Categories
    const char* categories[NUM_CATEGORIES] = {
        "Aces (1s)",
        "Twos (2s)",
        "Threes (3s)",
        "Fours (4s)",
        "Fives (5s)",
        "Sixes (6s)",
        "Three of a Kind",
        "Four of a Kind",
        "Full House",
        "Small Straight",
        "Large Straight",
        "Yahtzee",
        "Chance"
    };

    // Print scores for each category
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("| %-17s | %-15d | %-15d |\n", categories[i], player_scores[i], computer_scores[i]);
        
        // Print the sum and bonus rows after the Sixes row
        if (i == 5) {
            // Calculate the sum of the upper section (singles) for both player and computer
            int sum_upper_section_player = player_scores[0] + player_scores[1] + player_scores[2] + player_scores[3] + player_scores[4] + player_scores[5];
            int sum_upper_section_computer = computer_scores[0] + computer_scores[1] + computer_scores[2] + computer_scores[3] + computer_scores[4] + computer_scores[5];

            printf("------------------------------------------------------------\n");
            printf("| Sum Upper Section  | %-15d | %-15d |\n", sum_upper_section_player, sum_upper_section_computer);
            
            // Calculate and display bonus for both player and computer
            int bonus_player = (sum_upper_section_player >= BONUS_THRESHOLD) ? BONUS_POINTS : 0;
            int bonus_computer = (sum_upper_section_computer >= BONUS_THRESHOLD) ? BONUS_POINTS : 0;
            printf("| Bonus              | %-15d | %-15d |\n", bonus_player, bonus_computer);
            printf("------------------------------------------------------------\n");
        }
    }

    // Calculate total score (sum + bonus + other scores) for both player and computer
    int total_score_player = player_scores[6] + player_scores[7] + player_scores[8] + player_scores[9] + player_scores[10] + player_scores[11] + player_scores[12];
    int sum_upper_section_player = player_scores[0] + player_scores[1] + player_scores[2] + player_scores[3] + player_scores[4] + player_scores[5];
    total_score_player += sum_upper_section_player + (sum_upper_section_player >= BONUS_THRESHOLD ? BONUS_POINTS : 0);

    int total_score_computer = computer_scores[6] + computer_scores[7] + computer_scores[8] + computer_scores[9] + computer_scores[10] + computer_scores[11] + computer_scores[12];
    int sum_upper_section_computer = computer_scores[0] + computer_scores[1] + computer_scores[2] + computer_scores[3] + computer_scores[4] + computer_scores[5];
    total_score_computer += sum_upper_section_computer + (sum_upper_section_computer >= BONUS_THRESHOLD ? BONUS_POINTS : 0);

    // Print total scores for both player and computer
    printf("| Total Score        | %-15d | %-15d |\n", total_score_player, total_score_computer);
    printf("------------------------------------------------------------\n");
}
