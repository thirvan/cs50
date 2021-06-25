#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cipher(string text, int k);
void usage(void);
int validate_key(string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int k;
        k = validate_key(key);

        // printf("key: %s\n", key);
        // printf("k: %i\n", k);
        
        if (k != -1)
        {
            string text = get_string("plaintext: ");
            cipher(text, k);
            printf("ciphertext: %s\n", text);
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

    return 0;

}

void cipher(string text, int k)
{
    int offset = k % 26;
    // printf("+ %i\n", offset);

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int plain_ch = text[i];
        int cipher_ch = plain_ch;
        // printf("plain_ch %c %i\n", plain_ch, plain_ch); 
        if (isalpha(plain_ch))
        {
            cipher_ch += offset;
            // printf("cipher_ch before wrap %c %i\n", cipher_ch, cipher_ch);

            if ((islower(plain_ch) && cipher_ch > 'z' ) || (isupper(plain_ch) && cipher_ch > 'Z'))
            {
                cipher_ch -= 'Z' - 'A' + 1;
            }
        }
        // printf("cipher_ch %c %i\n", cipher_ch, cipher_ch); 
        text[i] = (char) cipher_ch;
    }
}

// Return the key as an int if it is a positive int, else return -1
int validate_key(string key)
{
    bool valid = true;
    int k = -1;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        char ch = key[i];
        if (ch < '0' || ch > '9')
        {
            valid = false;
        }
    }
    if (valid == true)
    {
        k = atoi(key);
    }

    return k;
}

void usage(void)
{
    printf("Usage: ./caesar key\n");
}