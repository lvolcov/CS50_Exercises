#include <stdio.h>
#include <cs50.h>

int collatz(int n);
int steps = 0;

int main (void)
{
    collatz(get_int("Number: "));
}

int collatz(int n)
{
    if (n == 1)
    {
        printf ("%i\n", steps);
        return 1;
    }
    else if ((n & 1))
    {
        steps++;
        return collatz(3 * n + 1);
    }
    else
    {
        steps++;
        return collatz(n / 2);
    }
}