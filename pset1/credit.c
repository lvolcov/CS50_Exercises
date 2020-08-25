#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    long number;
    int sum = 0;
    int sum_final = 0;
    long calc = 0;
    int begin = 0;
    
    
    //trava1
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);
    
    //checkvalid
    for (long divisor = 10; divisor < 10000000000000000; divisor = divisor * 100)
    {
        calc = number;
        calc = (calc / divisor) % 10;
        sum = calc * 2;
        sum_final = sum_final + (sum / 10 % 10) + (sum % 10);
        sum = 0;
        calc = 0;
    }
    for (long divisor = 1; divisor < 10000000000000000; divisor = divisor * 100)
    {
        calc = number;
        calc = (calc / divisor) % 10;
        sum_final = sum_final + calc;
        calc = 0;
    }
  
    
    //convert begin to int
    begin = (number / pow(10, 12));
    
    //which card
    if ((sum_final % 10) != 0)
    {
        printf("INVALID\n");
    }
    else if (((begin / 10) % 100) == 34 || ((begin / 10) % 100) == 37)
    {
        printf("AMEX\n");
    }
    else if (((begin / 100) % 100) >= 51 && ((begin / 100) % 100) <= 55)
    {
        printf("MASTERCARD\n");
    }    
    else if ((begin % 10) == 4 || ((begin / 1000) % 10) == 4)
    {
        printf("VISA\n");
    }        
    else
    {
        printf("INVALID\n");        
    }
}