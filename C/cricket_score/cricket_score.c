#include <stdio.h>

int main(void) {
    int num_of_players = 11;
    int scores[num_of_players];

    int highest_score = 0;
    int player_position = 0;
    for (int i = 0; i < 11; i++) {
        printf("Enter the score of player %d: ", i+1);
        scanf("%d", &scores[i]);

        if (scores[i] > highest_score) {
            highest_score = scores[i];
            player_position = i;
        }
    }
    printf("Highest score: %d by player %d\n", highest_score, player_position + 1);
    return 0;
}