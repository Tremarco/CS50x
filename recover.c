#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // ensure proper usage by checking argc is exactly 2
    if (argc != 2)
    {
        // if it isn't, prompt proper usage and return 1
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open input file in read mode
    FILE *input = fopen(argv[1], "r");

    // if forensic image cannot be opened for reading, inform user and return 1 from main
    if (input == NULL)
    {
        printf("Error: Unable to open file\n");
        return 1;
    }
    // define the block size
    int block_size = 512;
    // create space in memory to store 512 byte blocks in buffer when reading
    unsigned char buffer[block_size];
    // create space of 8 to store filename because "xxx.jpg" is 7, plus one more for null
    char filename[8];
    FILE *output = NULL;
    // variable for counting how many jpegs have been found
    int counter = 0;

    // while there is a block of 512 to read, do it. when there isn't, exit the loop.
    while (fread(buffer, block_size, 1, input) == 1)
    {
        // if we detect the beginning header of a jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it is the first jpeg we have found, create a new jpeg file and write to it from the buffer
            if (counter == 0)
            {
                // create a string for filename in correct "xxx.jpg" format using data from counter
                sprintf(filename, "%03i.jpg", counter);
                // open the file in write mode
                output = fopen(filename, "w");
                // write buffer to the file and increment the counter
                fwrite(&buffer, block_size, 1, output);
                counter++;
            }
            // if we already found a jpeg file
            else
            {
                // close the old one
                fclose(output);
                // create name for and open new file
                sprintf(filename, "%03i.jpg", counter);
                output = fopen(filename, "w");
                // write to it from the buffer and increment counter
                fwrite(&buffer, block_size, 1, output);
                counter++;

            }
        }
        // if we don't detect the beginning of a jpeg file
        else
        {
            // if we have already found a file and started writing
            if (counter > 0)
            {
                // continue writing to it from the buffer
                fwrite(&buffer, block_size, 1, output);
            }
        }
    }

    // ensure all files are closed
    fclose(output);
    fclose(input);

    // return 0 in main
    return 0;

}