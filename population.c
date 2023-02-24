#include <cs50.h>
#include <stdio.h>

// prototype for function
int calc_years(int s, int n);

int main(void)
{
    // Initialise variables to store start and end size
    int start_size;
    int end_size;

    // do/while loop to continually prompt user first for start size then for end size
    do
    {
        start_size = get_int("Enter starting population: ");
    }
    while (start_size < 9);


    do
    {
        end_size = get_int("Enter ending population: ");
    }
    while (end_size < start_size);

    // Call function to calculate number of years to get from start size to end size
    int y = calc_years(start_size, end_size);

    // Print number of years
    printf("Years: %i.\n", y);
}

int calc_years(int s, int e)
{
    // initialise counter variable to keep track of how many years iterated through in loop
    int years = 0;

    // as long as start size is less than end size
    while (s < e)
    {
        // adjust start population according to formula given
        s = s + (s / 3) - (s / 4);
        // increment years counter
        years++;
    }

    // return the number of years after exiting the loop
    return years;
}