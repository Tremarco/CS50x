// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // define an array of the relevant size in which to store the header when we read it
    uint8_t header[HEADER_SIZE];

    // read the header from the input file and into the array
    fread(header, HEADER_SIZE, 1, input);
    // write the header from the array and into the output file. No modification needed as should be identical
    fwrite(header, HEADER_SIZE, 1, output);

    // buffer sets up a space in memory of size int16t in which to store the data read
    int16_t buffer;
    // while there is a sample left to read in the file (will exit the loop and stop once there isn't a sample left to read)
    // read a single 2 bit sample and store it in buffer
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // multiply the sample that was stored in buffer by fread by the factor entered by user as command line arg
        buffer *= factor;
        // write the modified sample to the output file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
