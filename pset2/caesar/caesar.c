#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encipher(string text, int k);
void usage(void);
int validate_key(string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int k;
        k = validate_key(key);

        if (k != -1)
        {
            string text = get_string("plaintext: ");
            encipher(text, k);
            printf("ciphertext: %s\n", text);
            return 0;
        }
        else
        {
            usage();
            return 1;
        }
    }
    else
    {
        usage();
        return 1;
    }
}

// Encrypt text with the key k
void encipher(string text, int k)
{
    // Get number of shift to be between 0 and 25
    int offset = k % 26;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int plain_ch = (int) text[i];

        int cipher_ch = plain_ch;
        // If an alphabet, shift by k letters
        if (isalpha(plain_ch))
        {
            cipher_ch += offset;

            // If letter exceeds range of lower or uppercase, wrap back to 
            // correct letter
            if ((islower(plain_ch) && cipher_ch > 'z') || (isupper(plain_ch) && cipher_ch > 'Z'))
            {
                cipher_ch -= 'Z' - 'A' + 1;
            }
        }

        text[i] = (char) cipher_ch;
    }
}

// Return the key as an int if it is a positive int, else return -1
int validate_key(string key)
{
    bool valid = true;
    int k = -1;

    // Invalid if at least one character from key is not a digit
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        char ch = key[i];
        if (ch < '0' || ch > '9')
        {
            valid = false;
        }
    }

    // Convert key to int if valid else return is -1
    if (valid == true)
    {
        k = atoi(key);
    }

    return k;
}

// Print the usage message of the program
void usage(void)
{
    printf("Usage: ./caesar key\n");
}