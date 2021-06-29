#include <math.h>
#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + 
                    image[i][j].rgbtRed;
            int average = round(sum / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

int round_and_cap(float n)
{
    int result = round(n);

    if (result > 255)
    {
        result = 255;
    }
    return result;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = round_and_cap(.393 * originalRed 
                                              + .769 * originalGreen 
                                              + .189 * originalBlue);
            image[i][j].rgbtGreen= round_and_cap(.349 * originalRed 
                                              + .686* originalGreen 
                                              + .168* originalBlue);
            image[i][j].rgbtBlue= round_and_cap(.272* originalRed 
                                              + .534* originalGreen 
                                              + .131* originalBlue);
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int mid_idx = width / 2;
        for (int j = 0; j < mid_idx; j++)
        {
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
