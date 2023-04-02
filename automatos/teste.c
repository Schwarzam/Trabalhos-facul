#include <stdio.h>

int main() {
    char first_digit = '4';
    char second_digit = '2';

    int first_int = first_digit - '0';
    int second_int = second_digit - '0';

    int combined_number = first_int * 10 + second_int;

    printf("Combined number: %d\n", combined_number);

    return 0;
}