#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cipher(string text, int k);
void usage(void);
bool validate_key(string key);

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        // Array of booleans for each alphabet, becomes true when found in key


        if (validate_key(key) == true)
        {
            printf("valid key: %s\n", key);
            // string text = get_string("plaintext: ");
            // cipher(text, k);
            // printf("ciphertext: %s\n", text);
            return 0;
        }
        else
        {
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
void cipher(string text, int k)
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
bool validate_key(string key)
{
    bool valid = true;
    int k = -1;
    bool alphabets[26] = {false};

    // Validate length of key
    if (strlen(key) == 26)
    {

        for (int i = 0; i < 26 && valid == true; i++)
        {
            char ch = key[i];
            // Check if alphabet
            if (isalpha(ch))
            {
                ch = toupper(ch);
                // Get index of character in bool array
                int alpha_idx = ch - 'A';

                // New character
                if (alphabets[alpha_idx] == false)
                {
                    alphabets[ch - 'A'] = true;
                }
                // Repeated character
                else
                {
                    valid = false;
                    printf("Key must not contain repeated characters.\n");
                }

            }
            else
            {
                valid = false;
                printf("Key must only contain alphabetic characters.\n");
            }
        }

    }
    else
    {
        valid = false;
        printf("Key must contain 26 characters.\n");
    }

    return valid;
}

// Print the usage message of the program
void usage(void)
{
    printf("Usage: ./substitution key\n");
}