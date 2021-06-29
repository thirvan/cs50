#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"


int round_and_cap(float n);
void blur_pixel(int row, int col, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE new_image[height][width]);

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

void blur_pixel(int row, int col, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE new_image[height][width])
{
    float sum_red = 0;
    float sum_green = 0;
    float sum_blue = 0;
    int num_pixels = 0;

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int cur_row = row + i;
            int cur_col = col + j;
            if (cur_row >= 0 && cur_row < height 
             && cur_col >= 0 && cur_col < width)
            {
                sum_red += image[cur_row][cur_col].rgbtRed;
                sum_green += image[cur_row][cur_col].rgbtGreen;
                sum_blue += image[cur_row][cur_col].rgbtBlue;
                num_pixels++;
            }
        }
    }

    int avg_red = round(sum_red / num_pixels);
    int avg_green = round(sum_green / num_pixels);
    int avg_blue = round(sum_blue / num_pixels);

    new_image[row][col].rgbtRed = avg_red;
    new_image[row][col].rgbtGreen = avg_green;
    new_image[row][col].rgbtBlue = avg_blue;

}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blur_pixel(i, j, height, width, image, new_image);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }

    return;
}
