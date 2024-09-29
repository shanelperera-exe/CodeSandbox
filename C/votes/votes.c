#include <stdio.h>

void sort_votes(int votes[], int length);

int main(void) {
    int num_of_candidates = 5;
    int votes[num_of_candidates], original_votes[num_of_candidates];

    for (int i = 0; i < num_of_candidates; i++) {
        printf("Enter the number of votes of candidate %d: ", i + 1);
        scanf("%d", &votes[i]);
        original_votes[i] = votes[i];
    }

    sort_votes(votes, num_of_candidates);

    printf("Sorted votes: ");
    for (int n = 0; n < num_of_candidates; n++) {
        printf("%d ", votes[n]);
    }
    printf("\n");

    int max_vote = votes[num_of_candidates - 1];
    for (int j = 0; j < num_of_candidates; j++) {
        if (original_votes[j] == max_vote) {
            printf("Candidate %d wins with %d votes.\n", j + 1, max_vote);
            break;
        }
    }

    return 0;
}

void sort_votes(int votes[], int length) {
    for (int i = 0; i < length - 1; i++) {
        int min_vote_index = i;
    
        for (int j = i + 1; j < length; j++) {
            if (votes[j] < votes[min_vote_index]) {
                min_vote_index = j;
            }
        }

        if (min_vote_index != i) {
            int temp = votes[i];
            votes[i] = votes[min_vote_index];
            votes[min_vote_index] = temp;
        }
    }
}