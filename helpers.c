// Harvard CS50x - Week 4 - Problem Set 4 
// Filter: https://cs50.harvard.edu/x/psets/4/filter/more/
// Code basis structure provided by Harvard

#include "helpers.h"
#include <math.h>
#include <stdio.h>

void buffer(int height, int width, RGBTRIPLE image_original[height][width],
            RGBTRIPLE image_buffer[height][width]);
int cap(int number, int cap);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    int average;

    // Change RGB (BGR) values for its average
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;

            average = round((blue + green + red) / 3.0); // Float division avoids
                                                         // truncating before rounding

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    // Swap linear values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
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
    int blue_temp;
    int green_temp;
    int red_temp;
    int blue_average;
    int green_average;
    int red_average;
    float count; // Float avoids truncating in division before rounding

    RGBTRIPLE image_buffer[height][width];
    buffer(height, width, image, image_buffer);

    // Change center pixel's RGB (BGR) value for the average of 3x3 pixel block's RGB values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // reset temp values
            blue_temp = 0;
            green_temp = 0;
            red_temp = 0;
            count = 0;

            // 3x3 block around center pixel
            for (int i_c = (i - 1); i_c <= (i + 1); i_c++)
            {
                for (int j_c = (j - 1); j_c <= (j + 1); j_c++)
                {
                    if (i_c >= 0 && i_c < height && j_c >= 0 && j_c < width) // Pixels inside image
                    {
                        blue_temp += image_buffer[i_c][j_c].rgbtBlue;
                        green_temp += image_buffer[i_c][j_c].rgbtGreen;
                        red_temp += image_buffer[i_c][j_c].rgbtRed;

                        count++;
                    }
                }
            }
            blue_average = (int) round((blue_temp / count));
            green_average = (int) round((green_temp / count));
            red_average = (int) round((red_temp / count));

            image[i][j].rgbtBlue = blue_average;
            image[i][j].rgbtGreen = green_average;
            image[i][j].rgbtRed = red_average;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel Kernels
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE image_buffer[height][width];
    buffer(height, width, image, image_buffer);

    int blue_temp_gx;
    int blue_temp_gy;
    int green_temp_gx;
    int green_temp_gy;
    int red_temp_gx;
    int red_temp_gy;
    int blue_sobel;
    int green_sobel;
    int red_sobel;

    // Change center pixel's RGB (BGR) values by Sobel operator
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // reset temp values
            blue_temp_gx = 0;
            blue_temp_gy = 0;
            green_temp_gx = 0;
            green_temp_gy = 0;
            red_temp_gx = 0;
            red_temp_gy = 0;

            // 3x3 block around center pixel
            for (int i_c = (i - 1); i_c <= (i + 1); i_c++)
            {
                for (int j_c = (j - 1); j_c <= (j + 1); j_c++)
                {
                    if (i_c >= 0 && i_c < height && j_c >= 0 && j_c < width) // Pixels inside image
                    {
                        blue_temp_gx +=
                            (image_buffer[i_c][j_c].rgbtBlue * gx[i_c - (i - 1)][j_c - (j - 1)]);
                        blue_temp_gy +=
                            (image_buffer[i_c][j_c].rgbtBlue * gy[i_c - (i - 1)][j_c - (j - 1)]);

                        green_temp_gx +=
                            (image_buffer[i_c][j_c].rgbtGreen * gx[i_c - (i - 1)][j_c - (j - 1)]);
                        green_temp_gy +=
                            (image_buffer[i_c][j_c].rgbtGreen * gy[i_c - (i - 1)][j_c - (j - 1)]);

                        red_temp_gx +=
                            (image_buffer[i_c][j_c].rgbtRed * gx[i_c - (i - 1)][j_c - (j - 1)]);
                        red_temp_gy +=
                            (image_buffer[i_c][j_c].rgbtRed * gy[i_c - (i - 1)][j_c - (j - 1)]);
                    }
                }
            }
            blue_sobel = (int) round(sqrt((pow(blue_temp_gx, 2) + pow(blue_temp_gy, 2))));
            green_sobel = (int) round(sqrt((pow(green_temp_gx, 2) + pow(green_temp_gy, 2))));
            red_sobel = (int) round(sqrt((pow(red_temp_gx, 2) + pow(red_temp_gy, 2))));

            image[i][j].rgbtBlue = cap(blue_sobel, 255);
            image[i][j].rgbtGreen = cap(green_sobel, 255);
            image[i][j].rgbtRed = cap(red_sobel, 255);
        }
    }

    return;
}

void buffer(int height, int width, RGBTRIPLE image_original[height][width],
            RGBTRIPLE image_buffer[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_buffer[i][j] = image_original[i][j];
        }
    }
}

int cap(int number, int limit)
{
    if (number >= limit)
    {
        return limit;
    }
    else
    {
        return number;
    }
}
