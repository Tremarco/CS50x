#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// prototypes for letter, word and sentence count functions
int letter_count(char *text);
int word_count(char *text);
int sentence_count(char *text);

int main(void)
{
    // get text input from user
    char *text = get_string("Text: ");

    // call functions to calculate letter, word and sentence totals
    int letters = letter_count(text);
    int words = word_count(text);
    int sentences = sentence_count(text);

    // calculate average letters per 100 words
    float L = (float)letters / words * 100;
    // calculate average sentences per 100 words
    float S = (float)sentences / words * 100;
    // plug averages into Coleman-Liau formula and round to nearest int
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // if resulting index less than 1
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    // else if resulting index greater than 16
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    // otherwise
    else
    {
        printf("Grade %i\n", index);
    }
}

int letter_count(char *text)
{
    // initialise counter variable
    int counter = 0;

    // loop through all chars in text
    for (int i = 0; i < strlen(text); i++)
    {
        // if it is a letter
        if (isalpha(text[i]) != 0)
        {
            // increment counter
            counter++;
        }
    }

    return counter;
}

int word_count(char *text)
{
    // initialise counter
    int counter = 0;

    // loop through all chars in text
    for (int i = 0; i < strlen(text); i++)
    {
        // if it is a whitespace
        if (isspace(text[i]) != 0)
        {
            // increment counter
            counter++;
        }
    }

    // account for final word (as we assume text won't end with a space)
    counter++;

    return counter;
}

int sentence_count(char *text)
{
    // initialise counter variable
    int counter = 0;

    // loop through all chars in text
    for (int i = 0; i < strlen(text); i++)
    {

        // if text[i] is !, ? or . we can assume its the end of a sentence for purposes of this assignment
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            // increment counter
            counter++;
        }
    }

    return counter;
}