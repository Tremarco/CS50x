#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // if handles errors for incorrect number of command line arguments
    if (argc != 2)
    {
        printf("ERROR: Please input exactly 1 commandline arg. Usage: ./substitution key\n");
        return 1;
    }
    // else handles other errors in key
    else
    {
        int i = 0;
        char *key = argv[1];
        char seen[26] = {0};

        // Loop through each char in the array key
        for (i = 0; i < strlen(key); i++)
        {
            char c = key[i];
            if (isalpha(c) == 0)
            {
                // Print ERROR and return 1 if key[i] is not alphabetical character.
                printf("ERROR: Key cannot contain special characters or numbers.\n");
                return 1;
            }
            if (seen[toupper(c) - 'A']++ != 0)
            {
                // Print ERROR and return 1 if the key contains duplicate alphabetical characters
                printf("ERROR: Key contains same letter more than once.\n");
                return 1;
            }
        }
        if (i != 26)
        {
            // Print ERROR and return 1 if string length of key is not exactly 26 characters
            printf("ERROR: Key must contain exactly 26 letters. Usage: ./substitution key\n");
            return 1;
        }

    }
    // output "plaintext:  " and prompt user for plaintext message
    printf("plaintext:  ");
    string pt = get_string("");

    // output "ciphertext: "
    printf("ciphertext: ");

    // iterate through plain text message, evaluating character and printing apporpriate index of argv
    for (int i = 0, n = strlen(pt); i < n; i++)
    {
        // Save the plaintext character of [i] in char variable
        char ptchar = pt[i];

        if (isupper(ptchar))
        {
            // If ptchar is uppercase access the key index of that character by subtracting 65 from ascii value and save as char coded
            char coded = argv[1][ptchar - 65];
            printf("%c", toupper(coded));
        }
        else if (islower(ptchar))
        {
            // If ptchar is lowercase, do the same but subtracting 97 instead.
            char coded = argv[1][ptchar - 97];
            printf("%c", tolower(coded));
        }
        else
        {
            // If the ptchar is neither upper nor lowercase, print it unchanged.
            printf("%c", ptchar);
        }
    }

    // print new line
    printf("\n");
    // exit by returning 0 from main
    return 0;
}