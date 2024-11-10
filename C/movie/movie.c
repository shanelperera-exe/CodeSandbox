#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
#define NUM_OF_RATINGS 5

typedef struct {
    char title[BUFFER_SIZE];
    int ratings[NUM_OF_RATINGS];
} movie_t;

float calc_avg_rating(movie_t *movie);

int main(void) {
    movie_t movie = {"Inception", {5, 4, 5, 4, 5}};

    float avg_rating = calc_avg_rating(&movie);

    printf("Average Rating for %s: %.1f\n", movie.title, avg_rating);

    return 0;
}

float calc_avg_rating(movie_t *movie) {
    int sum_of_ratings = 0;

    for (int i = 0; i < NUM_OF_RATINGS; i++) {
        sum_of_ratings += movie->ratings[i];
    }

    float avg_rating = (float)sum_of_ratings / NUM_OF_RATINGS;

    return avg_rating;
}