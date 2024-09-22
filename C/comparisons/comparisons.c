#include <stdio.h>
#include <stdlib.h>

int compare(int a, int b);
int compare_absolute(int a, int b);
int max(int a, int b, int (*compare)(int, int));

int main(void) {
    int a, b;

    printf("a: ");
    scanf("%d", &a);

    printf("b: ");
    scanf("%d", &b);

    int simple_comparison = max(a, b, &compare);
    printf("Simple Comparison: max = %d\n", simple_comparison);

    int absolute_comparison = max(a, b, &compare_absolute);
    printf("Absolute Comparison: max = %d\n", absolute_comparison);

    return 0;
}

int compare(int a, int b) {
    if (a > b) 
        return 1;
    else if (b > a) 
        return -1;
    else {
        return 0;
    }  
}

int compare_absolute(int a, int b) {
    a = abs(a);
    b = abs(b);

    if (a > b) 
        return 1;
    else if (b > a) 
        return -1;
    else 
        return 0;
}

int max(int a, int b, int (*compare)(int, int)) {
    int result = compare(a, b);

    if (result > 0) 
        return a;
    else if (result < 0)
        return b;
    else
        return a;
}
