// Problem Set 2 - substitution

// libs
#include <stdio.h> //printf
#include <cs50.h> //get_string
#include <string.h> //strlen
#include <ctype.h> // isalpha, toupper, tolower

// we will be using functions to (a) validate key and (b) ciphertext
int validate_key(string key);
void ciphertext(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc == 2) // check if there is a single command-line argument
    {
        string key = argv[1];
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            key[i] = toupper(key[i]);
        }
        if (! validate_key(key))
        {
            string plaintext = get_string("plaintext: ");
            ciphertext(plaintext, key); // call ciphertext function passing plaintext and the cipher key
            printf("\n"); // print a new line after output ciphertext
            return 0; // key is valid and ciphertext is printed out
        }
        printf("Invalid KEY\n");
        return 1; // key is invalid
    }
    printf("Usage: ./substitution key\n");
    return 1; // invalid command-line argument
}

int validate_key(string key)
{
    // key must have 26 alphabetic and non repeated characters, considering case-insensitive
    // return 1 in case of an invalid key
    if (strlen(key) != 26) // check if key has 26 characters
    {
        printf("Key must contain 26 characters.\n");
        return 1; // key failed test
    }
    else
    {
        for (int i = 0, n = strlen(key) -1 ; i < n ; i++) // loop through all characters [i < n] in key
        {
            if (! isalpha(key[i])) // check key for non alphabetic characters
            {
                printf("Key must contain 26 alphabetic and non repeated characters.\n");
                return 1; // key failed test
            }
            else
            {
                for (int j = i + 1 ; j < n  ; j++) // loop from actual [i] to all characters [j < n] in sequence
                {
                    if (toupper(key[i]) == toupper(key[j])) // check key for repeated characters considering case-insensitive
                    {
                        printf("Key must contain 26 alphabetic and non repeated characters.\n");
                        return 1; // key failed test
                    }
                }
            }
        }
    }
    return 0; // key passed all tests
}

void ciphertext(string plaintext, string key) // void function so return nothing (just print ciphertext)
{
    string atoz = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //base line
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext) -1; i < n ; i++) // loop trough plaintext [n]
    {
        if(isalpha(plaintext[i])) // check if character[i] is a letter
        {
            for (int j = 0, k = strlen(atoz); j < k ; j++) // loop through baseline (A to Z = 26 positions)
            {
                if (toupper(plaintext[i]) == toupper(atoz[j])) // find the position of the letter in alphabet (1 to 26)
                {
                    if (isupper(plaintext[i])) // check if letter is uppercase
                    {
                        printf("%c", toupper(key[j])); // (uppercase) take the position in alphabet and cipherkey corresponding position
                    }
                    else
                    {
                        printf("%c", tolower(key[j])); // (lowercase) take the position in alphabet and cipherkey corresponding position
                    }
                }
            }
        }
        else
        {
            printf("%c", plaintext[i]); // if isn't a letter just print original character
        }
    }

}
