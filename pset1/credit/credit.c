#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_digit(long number, int d);
int get_num_digits(long number);
int get_sum_digits(long number);
int checksum(long number);

int main(void)
{
    long number;

    // prompt for input
    number = get_long("Number: ");

    if (checksum(number) == 0)
    {
        printf("checksum is 0\n");
    }
    else
    {
        printf("invalid\n");
    }


    return 0;
}

// get the number of digits in number
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

int get_sum_digits(long number)
{
    int numDigits = get_num_digits(number);
    int digit;
    int sum = 0;

    

    for (int i = 1; i < numDigits + 1; i++)
    {
        digit = get_digit(number, i);
        sum += digit;
    }

    return sum;
}

int checksum(long number)
{
    int numDigits;
    int digit;
    int sum1 = 0;
    int sum2 = 0;
    int checksum;

    numDigits = get_num_digits(number);

    printf("num digits: %i\n", numDigits);
    // printf("sum digits: %i\n", get_sum_digits(number));
    
    for (int i = 1; i < numDigits + 1; i ++)
    {
        digit = get_digit(number, i);

        if (i % 2 == 0)
        {
            // printf("other digit %i: %i, %i\n", i, digit, get_sum_digits(digit * 2));
            sum1 += get_sum_digits(digit * 2);
        }
        else
        {
            sum2 += digit;
        }
    }
    // printf("sum set 1: %i\n", sum1);
    // printf("sum set 2: %i\n", sum2);

    // for (int i = 1; i < numDigits + 1; i += 2)
    // {
    //     digit = get_digit(number, i);
    //     digitTimes2 = digit * 2;

    //     printf("other digit %i: %i, %i, %i\n", i, digit, digitTimes2 , get_sum_digits(digitTimes2));
    //     sum2 += digit;
    // }
    // printf("sum set 2: %i\n", sum2);

    // printf("total is %i with last digit %i\n", sum1 + sum2, get_digit((sum1 + sum2), 1));
    checksum = get_digit((sum1 + sum2), 1);

    return checksum;

}