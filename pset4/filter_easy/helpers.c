#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int limit(int n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round(((double)image[i][j].rgbtRed + (double)image[i][j].rgbtGreen + (double)image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int newred = round(0.393 * (double)image[i][j].rgbtRed + 0.769 * (double)image[i][j].rgbtGreen + 0.189 *
                               (double)image[i][j].rgbtBlue);
            int newgreen = round(0.349 * (double)image[i][j].rgbtRed + 0.686 * (double)image[i][j].rgbtGreen + 0.168 *
                                 (double)image[i][j].rgbtBlue);
            int newblue = round(0.272 * (double)image[i][j].rgbtRed + 0.534 * (double)image[i][j].rgbtGreen + 0.131 *
                                (double)image[i][j].rgbtBlue);
            image[i][j].rgbtRed = limit(newred);
            image[i][j].rgbtGreen = limit(newgreen);
            image[i][j].rgbtBlue = limit(newblue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, c = round((float)width / 2); j < c ; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy
    RGBTRIPLE copy[height][width];
    for (int c = 0; c < height; c++)
    {
        for (int o = 0; o < width; o++)
        {
            copy[c][o] = image[c][o];
        }
    }

    //make blur
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = 0, green = 0, red = 0, count = 0;

            for (long a = -1; a <= 1; a++)
            {
                for (long b = -1; b <= 1; b++)
                {
                    if (!((i == 0 && a == -1) || (j == 0 && b == -1) || (i == height - 1 && a == 1) || (j == width - 1 && b == 1)))
                    {
                        blue += copy[i + a][j + b].rgbtBlue;
                        green += copy[i + a][j + b].rgbtGreen;
                        red += copy[i + a][j + b].rgbtRed;
                        count++;
                    }
                }
            }
            image[i][j].rgbtBlue = round(blue / count);
            image[i][j].rgbtGreen = round(green / count);
            image[i][j].rgbtRed =  round(red / count);
        }
    }
    return;
}

int limit(int n)
{
    if (n > 255)
    {
        n = 255;
    }
    return n;
}