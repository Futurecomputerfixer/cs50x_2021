#include "helpers.h"
#include <math.h>
#include <stdio.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int x = image[i][j].rgbtBlue;
            int y = image[i][j].rgbtGreen;
            int z = image[i][j].rgbtRed;

            //shading algorithm
            double a = (((double)x + y + z) / 3);
            int shade = round(a);
            image[i][j].rgbtBlue = shade;
            image[i][j].rgbtGreen = shade;
            image[i][j].rgbtRed = shade;
        }
    }
    return;
}





// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int a = round(width / 2);

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < a ; j++)
        {
            int x = image[i][j].rgbtBlue;
            int temp1 = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtBlue = temp1;
            image[i][width - 1 - j].rgbtBlue = x;

            int y = image[i][j].rgbtGreen;
            int temp2 = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtGreen = temp2;
            image[i][width - 1 - j].rgbtGreen = y;

            int z = image[i][j].rgbtRed;
            int temp3 = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtRed = temp3;
            image[i][width - 1 - j].rgbtRed = z;
        }
    }
    return;
}






// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int tempblue[height][width];
    int tempgreen[height][width];
    int tempred[height][width];
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int blue = 0;
            int green = 0;
            int red = 0;
            int counter = 0;
            for (int a = -1 ; a < 2 ; a++)
            {
                for (int b = -1 ; b < 2 ; b++)
                {
                    if (i + a < 0 || i + a > height - 1 || j + b < 0 || j + b > width - 1)
                    {
                        continue;
                    }
                    blue = blue + image[i + a][j + b].rgbtBlue;
                    green = green + image[i + a][j + b].rgbtGreen;
                    red = red + image[i + a][j + b].rgbtRed;
                    counter++;
                }
            }

            tempblue[i][j] = round((float)blue / counter);
            tempgreen[i][j] = round((float)green / counter);
            tempred[i][j] = round((float)red / counter);
        }
    }

    //enter the color value from temp storage
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j].rgbtBlue = tempblue[i][j];
            image[i][j].rgbtGreen = tempgreen[i][j];
            image[i][j].rgbtRed = tempred[i][j];
        }
    }
    return;
}







// Detect edges
//the coding for bluring is too redundant. another more succinct use is applied
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    //the g values
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxBlue = 0;
            float gyBlue = 0;
            float gxGreen = 0;
            float gyGreen = 0;
            float gxRed = 0;
            float gyRed = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r < 0 || i + r > height - 1 || j + c < 0 || j + c > width - 1)
                    {
                        continue;//command continue move the reiteration back to the loop again, ignoring the rest of the code in that loop body
                    }


                    //the color value multiplied by the constant g values
                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            //store the color value in the temporary storgae
            int blue = roundg(gxBlue, gyBlue);
            int green = roundg(gxGreen, gyGreen);
            int red = roundg(gxRed, gyRed);

            //to cap the value no greater than 255
            int x = 255;
            if (blue > x)
            {
                blue = x;
            }

            if (green > x)
            {
                green = x;
            }

            if (red > x)
            {
                red = x;
            }

            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtRed = red;
        }
    }

    //color value transfer from temp to actual
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {


            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}

int roundg (float gx, float gy)
{
    int g = round(sqrt(gx * gx + gy * gy));
    return g;
}