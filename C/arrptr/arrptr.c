#include <stdio.h>
#include <string.h>

#define NUM_OF_WORDS 5
#define MAX_LENGTH_OF_A_WORD 50
#define INPUT_BUFFER_SIZE 500

int count_occurrences(char *words[], char *search_word);

int main(void) {
    char words[NUM_OF_WORDS][MAX_LENGTH_OF_A_WORD];
    char *word_ptrs[NUM_OF_WORDS];
    char search_word[MAX_LENGTH_OF_A_WORD];

    printf("List of words >>>>\n");
    for (int i = 0; i < NUM_OF_WORDS; i++) {
        printf("Word %d: ", i + 1);
        scanf("%s", words[i]);
        word_ptrs[i] = words[i];
    }
    printf("\n");

    printf("Enter the word to search: ");
    scanf("%s", search_word);
    printf("\n");

    int count = count_occurrences(word_ptrs, search_word);

    printf("The word '%s' appears %d times.\n", search_word, count);

    return 0;

}

int count_occurrences(char *words[], char *search_word) {
    int count = 0;

    for (int i = 0; i < NUM_OF_WORDS; i++) {
        if (strcmp(words[i], search_word) == 0) {
            count++;
        }
    }

    return count;
}