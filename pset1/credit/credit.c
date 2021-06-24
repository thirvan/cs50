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
    int numDigits, firstDigit, secondDigit;

    // prompt for input
    number = get_long("Number: ");
    numDigits = get_num_digits(number);

    if (checksum(number) == 0)
    {
        // get the first two digits
        firstDigit = get_digit(number, numDigits);
        secondDigit = get_digit(number, numDigits - 1);


        if (numDigits == 15 && firstDigit == 3)
        {
            if (secondDigit == 4 || secondDigit == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (numDigits == 16 && firstDigit == 5)
        {
            if (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || 
                secondDigit == 4 || secondDigit == 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if ((numDigits == 13 || numDigits == 16) && firstDigit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// get the number of digits in number
int get_num_digits(long number)
{
    int num_digits = 0;

    if (number == 0)
    {
        num_digits = 1;
    }
    else
    {
        while (number > 0)
        {
            number /= 10;
            num_digits++;
        }
    }

    return num_digits;
}

// get the digit d from number
int get_digit(long number, int d)
{
    long power =  pow(10, d - 1);
    // truncate number to get level; a number whose last digit is the digit d
    long level = number / power;
    // get the last digit from level
    int digit = level % 10;

    return digit;
}

// get the sum of the digits in number
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

// use the checksum algorithm on number and return the total's last digit
int checksum(long number)
{
    int numDigits;
    int digit;
    // store the sum of the digits not multiplied by 2
    int sum1 = 0;
    // store the sum of the sum of the digits of the digits multiplied by 2
    int sum2 = 0;
    int checksum;

    numDigits = get_num_digits(number);

    // loop for every digit from the first one to the last
    for (int i = 1; i < numDigits + 1; i ++)
    {
        digit = get_digit(number, i);

        // if it is divisible by 2, multiply it by 2, make a sum of the 
        // result's digits and increment sum1 by that sum 
        if (i % 2 == 0)
        {
            sum1 += get_sum_digits(digit * 2);
        }
        // if not divisible by 2, increment sum2 by the digit
        else
        {
            sum2 += digit;
        }
    }

    checksum = get_digit((sum1 + sum2), 1);

    return checksum;
}