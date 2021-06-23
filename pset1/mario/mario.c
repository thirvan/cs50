#include <stdio.h>
#include <cs50.h>


int get_height(void);

int main(void)
{
    int height;
    // prompt user to enter the height
    height = get_height();

    
    for (int row = 0; row < height; row++)
    {
        // print correct number of spaces before hashe(s)
        for (int col = 0; col < height - row - 1; col++)
        {
            printf(" ");
        }

        // print correct number of hashe(s)
        for (int col = 0; col <= row; col++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// prompt user to enter height until between 1 and 8
int get_height(void)
{
    int height;

    do
    {
        height = get_int("Height (between 1 and 8): ");
    }
    while (height < 1 || height > 8);

    return height;
 
}