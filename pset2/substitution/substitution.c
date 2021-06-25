#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encipher(string text, string k);
void usage(void);
bool validate_key(string key);

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];


        if (validate_key(key) == true)
        {
            string text = get_string("plaintext: ");
            encipher(text, key);
            printf("ciphertext: %s\n", text);
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

// Encipher text with key 
void encipher(string text, string key)
{

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int plain_ch = text[i];
        int cipher_ch = plain_ch;

        if (isalpha(plain_ch))
        {
            int alpha_idx;
            // If is an uppercase character substitute with corresponding 
            // uppercase character from key
            if (isupper(plain_ch))
            {
                alpha_idx = plain_ch - 'A';
                cipher_ch = toupper(key[alpha_idx]);
            }
            // If is a lowercase character substitute with corresponding 
            // lowercase character from key
            else
            {
                alpha_idx = plain_ch - 'a';
                cipher_ch = tolower(key[alpha_idx]);
            }
        }

        text[i] = cipher_ch;
    }
}

// Return true if the key is valid else return false
bool validate_key(string key)
{
    bool valid = true;
    // Array of booleans for each alphabet, becomes true when found in key
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