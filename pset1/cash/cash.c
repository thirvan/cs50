#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_change(void);

int main(void)
{
    int cents;
    int coins = 0;

    cents = get_change();

    while (cents != 0)
    {
        // try to remove a quarter
        if (cents >= 25)
        {
            cents -= 25;
        }
        // try to remove a dime
        else if (cents >= 10)
        {
            cents -= 10;
        }
        // try to remove a nickle
        else if (cents >= 5)
        {
            cents -= 5;
        }
        // try to remove a penny
        else if (cents >= 1)
        {
            cents -= 1;
        }
        // if this else clause is executed there is a problem with the logic
        else
        {
            printf("There is a bug with the logic\n");
        }

        coins++;
    }
    


    printf("%i\n", coins);
    return 0;
}

// prompt user for a non-negative amount of change in dollars and return that 
// amount in cents
int get_change(void)
{
    float dollars;
    int cents;

    do
    {
        dollars = get_float("Changed owed: ");
        // convert dollars to cents to the nearest penny
        cents = round(dollars * 100);
    }
    while (dollars < 0);
    


    return cents;
}