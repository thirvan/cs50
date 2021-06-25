#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Say hello to the name of the user
    string name = get_string("Enter your name: ");
    printf("hello, %s\n", name);
}