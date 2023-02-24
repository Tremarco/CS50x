#include "helpers.h"
#include <math.h>

// added a function to check sepia values do not exceed 255 or fall below 0, and fix them to correct value if they do
void sepiacheck(int *colour);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through each pixel in the 2D image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the average RGB value for that pixel first
            // divide by 3.0 to get float value, then round to nearest int to avoid losing accuracy
            int rgbaverage = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // set RGB values to all be that average
            image[i][j].rgbtBlue = rgbaverage;
            image[i][j].rgbtGreen = rgbaverage;
            image[i][j].rgbtRed = rgbaverage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through each pixel in the 2D image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the sepia versions of each RGB colour using the formula provided, rounding to nearest int
            int sepiaRed = round((image[i][j].rgbtRed * .393) + (image[i][j].rgbtGreen * .769) + (image[i][j].rgbtBlue * .189));
            int sepiaGreen = round((image[i][j].rgbtRed * .349) + (image[i][j].rgbtGreen * .686) + (image[i][j].rgbtBlue * .168));
            int sepiaBlue = round((image[i][j].rgbtRed * .272) + (image[i][j].rgbtGreen * .534) + (image[i][j].rgbtBlue * .131));

            // run each sepia colour through the sepiacheck function
            // modifies the sepia colour to 255 if it exceeds range, and to 0 if it falls below range.
            sepiacheck(&sepiaRed);
            sepiacheck(&sepiaGreen);
            sepiacheck(&sepiaBlue);

            // modify the RBG bytes to the corresponding sepia version
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row
    for (int i = 0; i < height; i++)
    {
        // swap the first HALF of the pixels with their corresponding counterpart
        for (int j = 0; j < width / 2; j++)
        {
            // temp values for each of the RGB colours in each pixel to allow us to swap
            // int tempR = image[i][j].rgbtRed;
            // int tempG = image[i][j].rgbtGreen;
            // int tempB = image[i][j].rgbtBlue;
            RGBTRIPLE temp = image[i][j];

            // // swap with horizontal counterpart's RGB colours
            // image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            // image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            // image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j] = image[i][width - j - 1];

            // // use temp values to put in image[i][j]'s RGB values into the horizontal counterpart
            // image[i][width - j - 1].rgbtRed = tempR;
            // image[i][width - j - 1].rgbtGreen = tempG;
            // image[i][width - j - 1].rgbtBlue = tempB;
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create copy of image to avoid blur affecting reading of next pixel's average values
    RGBTRIPLE copy[height][width];

    // populate the copy pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // temp variables to store averages
            int rgbtRed = 0;
            int rgbtGreen = 0;
            int rgbtBlue = 0;

            // Check if pixel is in top left corner
            if (i == 0 && j == 0)
            {
                // Do not try to access i - 1 or j - 1
                // calculate average of surrounding pixels from copy and write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 4.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 4.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 4.0);
            }
            // Check if pixel is in bottom right corner
            else if (i == (height -1) && j == (width -1))
            {
                // Don't try to access i + 1 or j + 1
                // calculate average of surrounding pixels from copy and write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed) / 4.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen) / 4.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue) / 4.0);
            }

            // Check if pixel is in top right corner
            else if (i == 0 && j == (width - 1))
            {
                // Don't try to access i-1 or j+1
                // calculate average of surrounding pixels from copy write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j-1].rgbtRed) / 4.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j-1].rgbtGreen) / 4.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j-1].rgbtBlue) / 4.0);
            }

            // Check if pixel is in bottom left corner
            else if (i == (height - 1) && j == 0)
            {
                // Don't try to access i + 1 or j - 1
                // calculate average of surrounding pixels from copy and write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed) / 4.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen) / 4.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue) / 4.0);
            }

            // Check if pixel is in top row
            else if (i == 0)
            {
                // Don't try to access i -1
                // calculate average of surrounding pixels from copy and write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j+1].rgbtRed) / 6.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 6.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 6.0);
            }

            // Check if pixel is in left column
            else if (j == 0)
            {
                // Don't try to access j -1
                // calculate average of surrounding pixels from copy and write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 6.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 6.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 6.0);
            }

            // check if pixel is in bottom row
            else if (i == (height -1))
            {
                // don't try to access i + 1
                // calculate average of surrounding pixels from copy and write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i-1][j+1].rgbtRed) / 6.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i-1][j+1].rgbtGreen) / 6.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i-1][j+1].rgbtBlue) / 6.0);
            }
            // check if pixel is in right hand column
            else if (j == (width -1))
            {
                // don't try to access j + 1
                // calculate average of surrounding pixels from copy and write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j-1].rgbtRed) / 6.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j-1].rgbtGreen) / 6.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j-1].rgbtBlue) / 6.0);
            }
            // If pixel is not on any edge or corner
            else
            {
                // calculate average of surrounding pixels from copy write new values into image
                rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j+1].rgbtRed) / 9.0);
                rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 9.0);
                rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 9.0);
            }

            image[i][j].rgbtRed = rgbtRed;
            image[i][j].rgbtGreen = rgbtGreen;
            image[i][j].rgbtBlue = rgbtBlue;
        }
    }
    return;
}

void sepiacheck(int *colour)
{
    if (*colour > 255)
    {
        *colour = 255;
        return;
    }
    else if (*colour < 0)
    {
        *colour = 0;
        return;
    }

    return;
}
