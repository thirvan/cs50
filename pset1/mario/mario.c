#include <stdio.h>
#include <cs50.h>


int get_height(void);

int main(void)
{
    int height;
    height = get_height();

    printf("height: %i\n", height);
}


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