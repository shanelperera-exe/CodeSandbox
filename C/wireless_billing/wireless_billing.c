#include <stdio.h>

int main(void) {
    const int DEFAULT_MINS = 600;
    const double BASE_RATE = 39.99;
    const double ADD_MIN_RATE = 0.40;
    const double TAX_RATE = 5.25;

    int weekday_mins, night_mins, weekend_mins, total_mins;
    double pretax_bill, avg_cost_per_min, tax, total_bill;
    
    printf("Enter the number of weekday minutes: ");
    scanf("%d", &weekday_mins);

    printf("Enter the number of night minutes: ");
    scanf("%d", &night_mins);

    printf("Enter the number of weekend minutes: ");
    scanf("%d", &weekend_mins);

    if (weekday_mins > DEFAULT_MINS) {
        pretax_bill = BASE_RATE + (weekday_mins - DEFAULT_MINS) * ADD_MIN_RATE;
    }
    else {
        pretax_bill = BASE_RATE;
    }

    total_mins = weekday_mins + night_mins + weekend_mins;
    avg_cost_per_min = pretax_bill / total_mins;
    tax = pretax_bill * (TAX_RATE / 100);
    total_bill = pretax_bill + tax;

    printf("------------------------------\n");
    printf("     Monthly Bill Summary     \n");
    printf("------------------------------\n");
    printf("Weekday minutes used: %d\n", weekday_mins);
    printf("Night minutes used  : %d\n", night_mins);
    printf("Weekend minutes used: %d\n", weekend_mins);
    printf("Total minutes used  : %d\n", total_mins);
    printf("------------------------------\n");
    printf("Pre-tax bill: $%.2f\n", pretax_bill);
    printf("Average cost per minute: $%.2f\n", avg_cost_per_min);
    printf("Taxes: $%.2f\n", tax);
    printf("Total bill: $%.2f\n", total_bill);
    printf("------------------------------\n");
    return 0;
}