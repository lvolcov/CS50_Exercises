#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdbool.h>

string valid_triangle(int side[]);

int main(void)
{

    int side[3];

    for ( int i = 0; i < 3; i++)
    {
        do
        {
            side[i] = get_int("lenght side %i? \n", i + 1);
        }
        while (side[i] < 0);
    }

    printf("This triangle is %s \n", valid_triangle(side));

}

string valid_triangle(int side[])
{
    if ((side[0] + side[1] <= side[2]) || (side[2] + side[0] <= side[1]) || (side[1] + side[2] <= side[0]))
    {
        return "true";
    }
    else
    {
        return "false";
    }
}
