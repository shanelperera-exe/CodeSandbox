#include <stdio.h>

void find_hottest_and_coldest(int temps[], int days, int *hottest_day, int *coldest_day);

int main(void) {
    int days = 7;
    int temperatures[days];
    int hottest_day, coldest_day; 

    for (int i = 0; i < days; i++) {
        printf("Enter temperature of day %d: ", i + 1);
        scanf("%d", &temperatures[i]);
    }

    find_hottest_and_coldest(temperatures, days, &hottest_day, &coldest_day);

    printf("Hottest day: Day %d with %d degrees.\n", hottest_day + 1, temperatures[hottest_day]);
    printf("Hottest day: Day %d with %d degrees.\n", coldest_day + 1, temperatures[coldest_day]);

    return 0;
}

void find_hottest_and_coldest(int temps[], int days, int *hottest_day, int *coldest_day) {
    int max_temp = temps[0];
    int min_temp = temps[0];
    *hottest_day = 0;
    *coldest_day = 0;

    for (int i = 0; i < days; i++) {
        if (temps[i] > max_temp) {
            max_temp = temps[i];
            *hottest_day = i;
        }
        if (temps[i] < min_temp) {
            min_temp = temps[i];
            *coldest_day = i;
        }
    }
}


