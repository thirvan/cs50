#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startsize = 0;
    int endsize = 0;
    int numyears = 0;

    // Prompt for start size
    do
    {
        startsize = get_int("Enter the start size (at least 9): ");
    }
    while (startsize < 9);


    // Prompt for end size
    do
    {
        endsize = get_int("Enter the end size (at least %i): ", startsize);
    }
    while (endsize < startsize);

    // Calculate number of years until we reach threshold
    while (startsize < endsize)
    {
        startsize = startsize + (startsize / 3) - (startsize / 4);
        numyears++;
    }

    // Print number of years
    printf("Years: %i\n", numyears);

}