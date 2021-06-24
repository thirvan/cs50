#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);

int main(void)
{
    string text = get_string("Text: ");
    printf("%i letter(s)\n", count_letters(text));
    printf("%i word(s)\n", count_words(text));
}

// return the amount of alphabetical characters from text
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++ )
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }

    return count;
}

// return the amount of words separated with a space in text
int count_words(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++ )
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    // increment count one extra time for the last word
    count++;

    return count;
}

