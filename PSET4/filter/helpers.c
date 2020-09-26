/*
Starting code by CS50
helpers.c made by Marco Silva
22/09/2020
*/

#include "helpers.h"
#include <math.h>

// average for grayscale
int average(int r, int g, int b)
{
    return round((r + g + b) / 3.0); // needs to be divided by 3.0 since we need a float number to round it up correctly.
}

int getSepiaRed(int r, int g, int b)
{
    int sepiaRed = round(.393 * r + .769 * g + .189 * b);

    if (sepiaRed < 0)
    {
        return 0;
    }
    else if (sepiaRed > 255)
    {
        return 255;
    }
    else
    {
        return sepiaRed;
    }
}

int getSepiaGreen(int r, int g, int b)
{
    int sepiaGreen = round(.349 * r + .686 * g + .168 * b);

    if (sepiaGreen < 0)
    {
        return 0;
    }
    else if (sepiaGreen > 255)
    {
        return 255;
    }
    else
    {
        return sepiaGreen;
    }
}

int getSepiaBlue(int r, int g, int b)
{
    int sepiaBlue = round(.272 * r + .534 * g + .131 * b);

    if (sepiaBlue < 0)
    {
        return 0;
    }
    else if (sepiaBlue > 255)
    {
        return 255;
    }
    else
    {
        return sepiaBlue;
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = average(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}



// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = getSepiaRed(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            int sepiaGreen = getSepiaGreen(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            int sepiaBlue = getSepiaBlue(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}


// swapping the adresses of the respective image elements
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
    return;

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            swap(&image[i][j], &image[i][width - j - 1]); // it's width - j - 1 because we don't go to the width size IE:10 it's 0-9 not 0-10
        }
    }
    return;
}

// Blur image
//this is brute forced and a disgusting copy pasted code... need to refactor with some functions but am lazy to do it now
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width]; // rgbtriple img to copy the image original values
    float red, green, blue;
    int max_size = width - 1;
    int max_length = height - 1;

    //copy img to use original values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j].rgbtRed = image[i][j].rgbtRed;
            img[i][j].rgbtGreen = image[i][j].rgbtGreen;
            img[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // we run through the original image to start to blur the img
    // corners need special attention
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0) //top left corner, we get a 2 x 2 grid
            {
                red = round((img[i][j].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j + 1].rgbtRed + img[i][j + 1].rgbtRed) / 4.0);
                green = round((img[i][j].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen + img[i][j + 1].rgbtGreen) / 4.0);
                blue = round((img[i][j].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j + 1].rgbtBlue + img[i][j + 1].rgbtBlue) / 4.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            else if (i == max_length && j == 0) //bottom left corner
            {
                red = round((img[i][j].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j + 1].rgbtRed) / 4.0);
                green = round((img[i][j].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j + 1].rgbtGreen) / 4.0);
                blue = round((img[i][j].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j + 1].rgbtBlue) / 4.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            else if (i == 0 && j == max_size) //top right corner
            {
                red = round((img[i][j].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j - 1].rgbtRed + img[i][j - 1].rgbtRed) / 4.0);
                green = round((img[i][j].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i][j - 1].rgbtGreen) / 4.0);
                blue = round((img[i][j].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j - 1].rgbtBlue + img[i][j - 1].rgbtBlue) / 4.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            else if (i == max_length && j == max_size) //bottom right corner
            {
                red = round((img[i][j].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j - 1].rgbtRed + img[i][j - 1].rgbtRed) / 4.0);
                green = round((img[i][j].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j - 1].rgbtGreen + img[i][j - 1].rgbtGreen) / 4.0);
                blue = round((img[i][j].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j - 1].rgbtBlue + img[i][j - 1].rgbtBlue) / 4.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            //top row
            else if (i == 0 && (j > 0 && j < max_size))
            {
                red = round((img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j - 1].rgbtRed +
                            img[i + 1][j + 1].rgbtRed) / 6.0);
                green = round((img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen +
                            img[i + 1][j + 1].rgbtGreen) / 6.0);
                blue = round((img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j - 1].rgbtBlue +
                            img[i + 1][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            //left border

            else if (i > 0 && j == 0)
            {
                red = round((img[i][j].rgbtRed + img[i - 1][j].rgbtRed + img[i + 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j + 1].rgbtRed +
                            img[i + 1][j + 1].rgbtRed) / 6.0);
                green = round((img[i][j].rgbtGreen + img[i - 1][j].rgbtGreen + img[i + 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j + 1].rgbtGreen +
                            img[i + 1][j + 1].rgbtGreen) / 6.0);
                blue = round((img[i][j].rgbtBlue + img[i - 1][j].rgbtBlue + img[i + 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j + 1].rgbtBlue +
                            img[i + 1][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            //bottom row
            else if (i == max_length && (j > 0 && j < max_size))
            {
                red = round((img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i][j + 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j - 1].rgbtRed +
                            img[i - 1][j + 1].rgbtRed) / 6.0);
                green = round((img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j - 1].rgbtGreen
                            + img[i - 1][j + 1].rgbtGreen) / 6.0);
                blue = round((img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j + 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j - 1].rgbtBlue +
                            img[i - 1][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            //right border
            else if (i > 0 && j == max_size)
            {
                red = round((img[i][j].rgbtRed + img[i - 1][j].rgbtRed + img[i + 1][j].rgbtRed + img[i - 1][j - 1].rgbtRed + img[i][j - 1].rgbtRed +
                            img[i + 1][j - 1].rgbtRed) / 6.0);
                green = round((img[i][j].rgbtGreen + img[i - 1][j].rgbtGreen + img[i + 1][j].rgbtGreen + img[i - 1][j - 1].rgbtGreen + img[i][j - 1].rgbtGreen +
                            img[i + 1][j - 1].rgbtGreen) / 6.0);
                blue = round((img[i][j].rgbtBlue + img[i - 1][j].rgbtBlue + img[i + 1][j].rgbtBlue + img[i - 1][j - 1].rgbtBlue + img[i][j - 1].rgbtBlue +
                            img[i + 1][j - 1].rgbtBlue) / 6.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            //middle
            else if ((i > 0 && i < max_length) && (j > 0 && j < max_size))
            {
                red = round((img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i][j + 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j - 1].rgbtRed +
                            img[i - 1][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j - 1].rgbtRed + img[i + 1][j + 1].rgbtRed) / 9.0);
                green = round((img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j - 1].rgbtGreen +
                            img[i - 1][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen) / 9.0);
                blue = round((img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j + 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j - 1].rgbtBlue +
                            img[i - 1][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j - 1].rgbtBlue + img[i + 1][j + 1].rgbtBlue) / 9.0);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }
        }
    }
    return;
}
