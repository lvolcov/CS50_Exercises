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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float Gx[3][3] = 
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    float Gy[3][3] = 
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    //make copy
    RGBTRIPLE copy[height][width];
    for (int c = 0; c < height; c++)
    {
        for (int o = 0; o < width; o++)
        {
            copy[c][o] = image[c][o];
        }
    }

    //make edge
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float bluex = 0, greenx = 0, redx = 0;
            float bluey = 0, greeny = 0, redy = 0;

            for (long a = 0; a < 3; a++)
            {
                for (long b = 0; b < 3; b++)
                {
                    if (!((i == 0 && a == 0) || (j == 0 && b == 0) || (i == height - 1 && a == 2) || (j == width - 1 && b == 2)))
                    {
                        bluex += copy[i + a - 1][j + b - 1].rgbtBlue * Gx[a][b];
                        greenx += copy[i + a - 1][j + b - 1].rgbtGreen * Gx[a][b];
                        redx += copy[i + a - 1][j + b - 1].rgbtRed * Gx[a][b];

                        bluey += copy[i + a - 1][j + b - 1].rgbtBlue * Gy[a][b];
                        greeny += copy[i + a - 1][j + b - 1].rgbtGreen * Gy[a][b];
                        redy += copy[i + a - 1][j + b - 1].rgbtRed * Gy[a][b];
                    }
                }

            }
            image[i][j].rgbtBlue = limit(round(sqrt(pow(bluex, 2) + pow(bluey, 2))));
            image[i][j].rgbtGreen = limit(round(sqrt(pow(greenx, 2) + pow(greeny, 2))));
            image[i][j].rgbtRed = limit(round(sqrt(pow(redx, 2) + pow(redy, 2))));
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