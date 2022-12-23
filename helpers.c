#include "helpers.h"
#include "stdio.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= (height - 1); i++)
    {
        for (int j = 0; j <= (width - 1); j++)
        {
            //determine the average of the amount of red green and blue in the pixel
            int average = round(((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (double)3));
            //set rgb to the average value
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= (height - 1); i++)
    {
        for (int j = 0; j <= (width - 1); j++)
        {
            //creating variables for original rgbt values
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;
            int originalBlue = image[i][j].rgbtBlue;
            //determining the sepia value using the sepia formula for each color
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            //if any of the values are over 256 they will be set to the maximum 8 bit value of 255
            if (sepiaRed >= 256)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen >= 256)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue >= 256)
            {
                sepiaBlue = 255;
            }

            //the new sepia values are assigned to the pixel
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
    for (int i = 0; i <= (height - 1); i++) //for each row
    {

        for (int j = 0; j <= ((width - 1) / 2); j++) //for each pixel in the row
        {
            //store the value of the position that is being replaced ((width - 1) - j)
            RGBTRIPLE reflectval = image[i][(width - 1) - j];

            //replace the ((width - 1) - j) position with the ([i][j]) position
            image[i][(width - 1) - j] = image[i][j];

            //put the ((width - 1) - j) position value into the ([i][j]) position
            image[i][j] = reflectval;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j]; //just iterates through each pixel and assigns the value to cop[i][j]
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* creating variables for the sums of each color value as well as a counter which will keep track
            of how many pixels were used to calculate the average */
            float sum_red = 0;
            float sum_blue = 0;
            float sum_green = 0;
            int counter = 0;

            //2d loop to check all 9 pixels that contribute to the average
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    //makes sure that the pixel we are looking at is inside the image
                    if (i+y < 0 || i+y > height-1 || j+x < 0 || j+x > width-1)
                    {
                        continue;
                    }
                    //add the pixel value to sum_color until we are done looking at those 9 pixels
                    sum_red += copy[i+y][j+x].rgbtRed;
                    sum_blue += copy[i+y][j+x].rgbtBlue;
                    sum_green += copy[i+y][j+x].rgbtGreen;
                    counter++;
                }
            }
            //the sum of the pixels is divided by the amount of pixels that made up the sum, this is rounded and is our new pixel value
            image[i][j].rgbtRed = round(sum_red / (double)counter);
            image[i][j].rgbtBlue = round(sum_blue / (double)counter);
            image[i][j].rgbtGreen = round(sum_green / (double)counter);
        }
    }

    return;
}
