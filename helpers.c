#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int t = height;
    int l = width;
    float av;
    int av1;

    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < l; j++)
        {
            av = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            av1 = av / 1;
            if (av - av1 < 0.5)
            {
                image[i][j].rgbtRed = av1;
                image[i][j].rgbtGreen = av1;
                image[i][j].rgbtBlue = av1;
            }
            else
            {
                 image[i][j].rgbtRed = av1 +1;
                 image[i][j].rgbtGreen = av1 + 1;
                 image[i][j].rgbtBlue = av1 + 1;
            }
        }


    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel[height][width];

    //copy first in another image;
    for ( int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            pixel[i][j].rgbtRed = image[i][j].rgbtRed;
            pixel[i][j].rgbtGreen = image[i][j].rgbtGreen;
            pixel[i][j].rgbtBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = pixel[i][j].rgbtRed;
            image[i][width - 1 - j].rgbtGreen = pixel[i][j].rgbtGreen;
            image[i][width - 1 - j].rgbtBlue = pixel[i][j].rgbtBlue;
        }
    }

    return;
}






// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel[height][width];
    float Red = 0;
    int Green = 0;
    int Blue = 0;

    int f= 0;


     for ( int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                for (int n = -1; n < 2; n++)
                {
                    for (int z = -1; z < 2; z++)
                    {
                        //If top row
                        if((i + n) < 0)
                            //  And If edge
                            if((j+z) <0)
                            {
                                Red += image[i + n + 1][j + z + 1].rgbtRed;
                                Green += image[i + n+1][j + z + 1].rgbtGreen;
                                Blue += image[i + n+1][j + z + 1].rgbtBlue;
                                f=4;
                            }
                            //And Right edge
                            else if((j+z) > width)
                            {
                                Red += image[i + n + 1][j + z - 1].rgbtRed;
                                Green += image[i + n+1][j + z - 1].rgbtGreen;
                                Blue += image[i + n+1][j + z - 1].rgbtBlue;
                                f=4;
                            }
                            else
                            {
                                Red += image[i + n + 1][j + z].rgbtRed;
                                Green += image[i + n+1][j + z].rgbtGreen;
                                Blue += image[i + n+1][j + z].rgbtBlue;
                                f=6;
                            }
                        else if((i+n) > height)
                            if((j+z) <0)
                            {
                                Red += image[i + n - 1][j + z + 1].rgbtRed;
                                Green += image[i + n-1][j + z + 1].rgbtGreen;
                                Blue += image[i + n-1][j + z + 1].rgbtBlue;
                                f=4;
                            }
                            else if((j+z) > width)
                            {
                                Red += image[i + n - 1][j + z - 1].rgbtRed;
                                Green += image[i + n-1][j + z - 1].rgbtGreen;
                                Blue += image[i + n-1][j + z - 1].rgbtBlue;
                                f=4;
                            }
                            else
                            {
                                Red += image[i + n - 1][j + z].rgbtRed;
                                Green += image[i + n-1][j + z].rgbtGreen;
                                Blue += image[i + n-1][j + z].rgbtBlue;
                                f=6;
                            }
                            //Left Column is less than 0
                        else if((j+z) < 0 )
                            if((i+n)< 0)
                            {
                                Red += image[i + n + 1 ][j + z+ 1].rgbtRed;
                                Green += image[i + n+ 1][j + z + 1].rgbtGreen;
                                Blue += image[i + n+ 1][j + z + 1].rgbtBlue;
                                f=4;
                            }
                            else if((i+n) > height)
                            {
                               Red += image[i + n - 1 ][j + z+ 1].rgbtRed;
                                Green += image[i + n- 1][j + z + 1].rgbtGreen;
                                Blue += image[i + n- 1][j + z + 1].rgbtBlue;
                                f=4;
                            }
                            else
                            {
                                Red += image[i + n ][j + z+ 1].rgbtRed;
                                Green += image[i + n][j + z + 1].rgbtGreen;
                                Blue += image[i + n][j + z + 1].rgbtBlue;
                                f=6;
                            }
                        //If column is bigger than width
                        else if((j+z) > width)
                            if((i+n)< 0)
                            {
                                Red += image[i + n + 1 ][j + z- 1].rgbtRed;
                                Green += image[i + n+ 1][j + z - 1].rgbtGreen;
                                Blue += image[i + n+ 1][j + z - 1].rgbtBlue;
                                f=4;
                            }
                            else if((i+n) > height)
                            {
                               Red += image[i + n - 1 ][j + z- 1].rgbtRed;
                                Green += image[i + n- 1][j + z - 1].rgbtGreen;
                                Blue += image[i + n- 1][j + z - 1].rgbtBlue;
                                f=4;
                            }
                            else
                            {
                                Red += image[i + n ][j + z- 1].rgbtRed;
                                Green += image[i + n][j + z - 1].rgbtGreen;
                                Blue += image[i + n][j + z - 1].rgbtBlue;
                                f=6;
                            }
                        //If pixel is central
                        else
                        {
                            Red += image[i + n ][j + z].rgbtRed;
                            Green += image[i + n][j + z ].rgbtGreen;
                            Blue += image[i + n][j + z ].rgbtBlue;
                            f=9;
                        }
                    }
                }

                float y=0;
                y = (float)f;
                Red = Red / y;
                Green = Green / y;
                Blue = Blue / y;
                if(Red - (int)Red >=0.5)
                {
                    Red= Red /1 + 1;
                    pixel[i][j].rgbtRed = Red;
                }
                else
                {
                    pixel[i][j].rgbtRed = (int)Red;
                }


                if(Green - (int)Green >=0.5)
                {
                    Green= Green /1 + 1;
                    pixel[i][j].rgbtGreen = Green;
                }
                else
                {
                    pixel[i][j].rgbtGreen = (int)Green;
                }

                if(Blue - (int)Blue >= 0.5)
                {
                    Blue= Blue /1 + 1;
                    pixel[i][j].rgbtBlue = Blue;
                }
                else
                {
                    pixel[i][j].rgbtBlue = (int)Blue;
                }



                Red = 0;
                Green = 0;
                Blue = 0;
        }
    }

    for ( int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtRed = pixel[i][j].rgbtRed;
            image[i][j].rgbtGreen = pixel[i][j].rgbtGreen;
            image[i][j].rgbtBlue = pixel[i][j].rgbtBlue;
        }
    }
    return;
}




// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE pixel[height][width];
    int n = 0;
    int z = 0;
    int Red = 0;
    int Green = 0;
    int Blue = 0;
    int Redy = 0;
    int Bluey = 0;
    int Greeny = 0;

    for ( int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            for ( int x = -1; x < 2; x++)
            {
                for ( int y = -1; y < 2; y++)
                {
                    n = 0;
                    z = 0;
                    Red += image[i + x][j + y].rgbtRed * Gx[n][z];
                    Green += image[i + x][j + y].rgbtGreen * Gx[n][z];
                    Blue += image[i + x][j + y].rgbtBlue * Gx[n][z];
                    z++;
                }
                n++;
            }

            for(int t = -1; t < 2; t++)
            {
                for( int v = -1; v < 2; v++)
                {
                    n = 0;
                    z = 0;
                    Redy += image[i + t][j + v].rgbtRed * Gy[n][z];
                    Greeny += image[i + t][j + v].rgbtGreen * Gy[n][z];
                    Bluey += image[i + t][j + v].rgbtBlue * Gy[n][z];
                    z++;
                }
                n++;
            }

            pixel[i][j].rgbtRed = sqrt((Red * Red) + (Redy * Redy));
            pixel[i][j].rgbtGreen = sqrt((Green * Green) + (Greeny * Greeny));
            pixel[i][j].rgbtBlue = sqrt((Blue * Blue) + (Bluey * Bluey));
            Red = 0;
            Green = 0; Blue = 0; Redy = 0; Greeny = 0; Bluey = 0;
        }
    }

        for (int i = 1; i < height - 1; i ++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                image[i][j].rgbtRed = pixel[i][j].rgbtRed;
                image[i][j].rgbtGreen = pixel[i][j].rgbtGreen;
                image[i][j].rgbtBlue = pixel[i][j].rgbtBlue;
            }
        }
    return;
}
