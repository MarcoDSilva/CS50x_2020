/*
Made by Marco Silva
Substituition - CS50 PSET2
11/09/2020 - 12/09/2020
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    char keyToSwap[26];

    if (argc == 2)
    {
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            //verifying if the key is entirely alphabetic
            string key = argv[1];

            for (int i = 0; i < 26; i++)
            {
                // if it's not alphabetic
                if (isalpha(key[i]) == 0)
                {
                    printf("Key must only contain alphabetic characters.\n");
                    return 1;
                }

                // searching for repeated characters in the key to swap
                for (int j = 0; j < strlen(keyToSwap); j++)
                {
                    if (keyToSwap[j] == key[i])
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 1;
                    }
                }
                keyToSwap[i] = key[i]; // adding the new chara to the array in the same position
            }
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // instead of using the wheels from cs50.h , I resort here to the C normal types
    // so declared an array of chars, the input is with fgets (to allow spaces, and with a limit of size 100, since we don't need much in this exercise)
    char plaintext[100];
    printf("plaintext: ");
    fgets(plaintext, 100, stdin);

    int textSize = strlen(plaintext);
    char ciphertext[textSize];

    // cyphering the received input:
    // First we verify if the char is alphabetic, and if it is, we loop through the key to find the respective new char
    //  then we evaluate if it's upper/lower case, to decide what to send to the cipher.
    // Else we just add the non alphabetic chara to the cipher.
    for (int i = 0; i < textSize; i++)
    {
        if (isalpha(plaintext[i]) == 0)
        {
            ciphertext[i] = plaintext[i];
        }
        else
        {
            for (int j = 0; j < 26; j++)
            {
                if (toupper(plaintext[i]) == toupper(alphabet[j])) // both capitalized for a better comparison
                {
                    if (islower(plaintext[i]))
                    {
                        ciphertext[i] = tolower(keyToSwap[j]);
                    }
                    else if (isupper(plaintext[i]))
                    {
                        ciphertext[i] = toupper(keyToSwap[j]);
                    }
                }
            }
        }
    }
    printf("ciphertext: %s", ciphertext);

    return 0;
}