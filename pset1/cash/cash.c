#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_change(void);

int main(void)
{
    int cents;
    cents = get_change();


    printf("cents: %i\n", cents);
    return 0;
}

int get_change(void)
{
    float dollars;
    int cents;

    do
    {
        dollars = get_float("Changed owed: ");
        cents = round(dollars * 100);
    } while (dollars < 0);
    


    return cents;
}