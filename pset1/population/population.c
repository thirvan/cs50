#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startSize = 0;

    // TODO: Prompt for start size
    do
    {
        startSize = get_int("Enter the start size (should be at least 9): ");
    }
    while (startSize < 9);

    printf("Start size: %i\n", startSize);

    // TODO: Prompt for end size

    // TODO: Calculate number of years until we reach threshold

    // TODO: Print number of years
}