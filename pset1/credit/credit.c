#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_digit(long number, int d);
int get_num_digits(long number);

int main(void)
{
    long number;
    
    int num_digits;

    // prompt for input
    number = get_long("Number: ");
    num_digits = get_num_digits(number);
    printf("num digits: %i\n", num_digits);
    
    for (int i = 1; i < num_digits + 1; i++)
    {
        printf("digit %i: %i\n", i, get_digit(number, i));
    }

    printf("number: %li\n", number);

    return 0;
}

int get_num_digits(long number)
{
    int count = 0;

    if (number == 0)
    {
        count = 1;
    }
    else
    {
        while (number > 0)
        {
            number /= 10;
            count++;
        }
    }

    return count;
}

// get the digit d from number
int get_digit(long number, int d)
{
    long power =  pow(10, d - 1);
    long level = number / power;
    int digit = level % 10;

    return digit;
}