#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    int cents;
    int coins = 0;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int pennie = 1;
    float change;
    
    //trava
    do
    {
        change = get_float("Change owed: ");
    }
    while (change <= 0);
    
    //contador de moedas
    cents = round(change * 100);
    
    do
    {
        if (cents >= quarter)
        {
            cents = cents - quarter;
            coins++;
        }
        else if (cents >= dime && cents < quarter)
        {
            cents = cents - dime;
            coins++;
        }
        else if (cents >= nickel && cents < dime)
        {
            cents = cents - nickel;
            coins++;
        }
        else
        {
            cents = cents - pennie;
            coins++;
        }
        
    }
    while (cents != 0);
    printf("%i\n", coins);
}