#include <stdio.h>
#include <cs50.h>


int get_height(void);
void print_hashes(int n);

int main(void)
{
    int height;
    // prompt user to enter the height
    height = get_height();

    
    for (int row = 1; row < height + 1; row++)
    {
        // print gap before hashes
        for (int col = 0; col < height - row; col++)
        {
            printf(" ");
        }
        // print left hashes
        print_hashes(row);

        // print gap between hashes
        printf("  ");

        // print right hashes
        print_hashes(row);


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

// print n hashes
void print_hashes(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}