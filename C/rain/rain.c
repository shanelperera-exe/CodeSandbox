#include <stdio.h>

#define WEEKS 4
#define DAYS 7

int main(void) {
    int rainfall_data[4][7] = {
        {3, 0, 5, 2, 0, 1, 6},
        {7, 0, 3, 4, 2, 8, 5}, 
        {2, 1, 5, 3, 0, 2, 7},
        {6, 0, 8, 2, 4, 1, 5}
    };

    int overall_sum = 0;
    for (int week = 0; week < WEEKS; week++) {
        int sum = 0;
        for (int day = 0; day < DAYS; day++) {
            sum += rainfall_data[week][day];
        }
        printf("Week %d total: %d mm\n", week + 1, sum);
        overall_sum += sum;
    }
    int overall_average = overall_sum / WEEKS;

    printf("Overall average: %d mm\n", overall_average);

    return 0;
}