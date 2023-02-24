#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // do while loop to request int for height and reprompt until user complies with params
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);


    // nested for loops, 1 outer 3 inner
    // outside loop for generating rows = height, inside loops for generating content of the rows
    for (int i = 1; i <= height; i++)
    {
        // inside loop 1 for printing spaces before #'s)
        for (int j = 1; j <= height - i; j++)
        {
            printf(" ");
        }
        // inside loop 2 for printing #'s themselves
        for (int j = i; j < 2 * i; j++)
        {
            printf("#");
        }
        // printf command outside the first 2 inner loops to add spaces at the end of each finished left side row (to seperate pyramids)
        printf("  ");
        // inside loop 3 to print number of # required for right side of the row
        for (int j = i; j < 2 * i; j++)
        {
            printf("#");
        }
        // new line command to move us onto the next row on a new line.
        printf("\n");
    }
}