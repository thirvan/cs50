#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int round_and_cap(float n);
void blur_pixel(int row, int col, int height, int width, 
                RGBTRIPLE image[height][width], 
                RGBTRIPLE new_image[height][width]);
void sobel_pixel(int row, int col, int height, int width, 
                 RGBTRIPLE image[height][width], 
                 RGBTRIPLE new_image[height][width]);
int sobel_value(int row, int col, int height, int width, 
                RGBTRIPLE image[height][width], char color);

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int mid_idx = width / 2;
        // Loop for each pixel in a row until its middle
        for (int j = 0; j < mid_idx; j++)
        {
            // Swap the left pizel with its corresponding right pixel
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Make the average of the RGB values of the pixel at image[row][col] and store 
// it in new_image[row][col]
void blur_pixel(int row, int col, int height, int width, 
                RGBTRIPLE image[height][width], 
                RGBTRIPLE new_image[height][width])
{
    float sum_red = 0;
    float sum_green = 0;
    float sum_blue = 0;
    int num_pixels = 0;

    // Loop for the 9 pixels surrounding and including the middle one with i 
    // and j as offsets for the row and column positions
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int cur_row = row + i;
            int cur_col = col + j;
            // Check if the indices exist in the image
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
            blur_pixel(i, j, height, width, image, new_image);
        }
    }

    // Replace the original image with the updated new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }

    return;
}

// Round n to the closest integer and cap it at 255
int round_and_cap(float n)
{
    int result = round(n);

    if (result > 255)
    {
        result = 255;
    }
    return result;
}

// Calculate the sobel value of a given color
int sobel_value(int row, int col, int height, int width, 
                RGBTRIPLE image[height][width], char color)
{
    float sum_Gx = 0;
    float sum_Gy = 0;
    int kernelx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernely[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int color_value;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int cur_row = row + i;
            int cur_col = col + j;

            // Check if the index exist in the image
            if (cur_row >= 0 && cur_row < height 
                && cur_col >= 0 && cur_col < width)
            {
                switch (color)
                {
                    case 'R':
                        color_value = image[cur_row][cur_col].rgbtRed;
                        break;
                    case 'G':
                        color_value = image[cur_row][cur_col].rgbtGreen;
                        break;
                    case 'B':
                        color_value = image[cur_row][cur_col].rgbtBlue;
                        break;
                    
                    default:
                        fprintf(stderr, "Error with char passed to sobel_value()\n");
                        return -1;
                }
            }
            else
            {
                color_value = 0;
            }

            sum_Gx += color_value * kernelx[i + 1][j + 1];
            sum_Gy += color_value * kernely[i + 1][j + 1];
        }
    }
    float Gx = sum_Gx;
    float Gy = sum_Gy;

    return round_and_cap(sqrt(Gx * Gx + Gy * Gy));
}

// Calculate the new pixel value using the sobel operator
void sobel_pixel(int row, int col, int height, int width, 
                 RGBTRIPLE image[height][width], 
                 RGBTRIPLE new_image[height][width])
{
    // Calculate the sobel value for each color channel
    new_image[row][col].rgbtRed = sobel_value(row, col, height, width, image, 'R');
    new_image[row][col].rgbtGreen = sobel_value(row, col, height, width, image, 'G');
    new_image[row][col].rgbtBlue = sobel_value(row, col, height, width, image, 'B');
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sobel_pixel(i, j, height, width, image, new_image);
        }
    }

    // Replace the original image with the updated new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}


