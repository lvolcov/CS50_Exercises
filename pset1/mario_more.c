#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n, i, j;

    //trava pra numero de 1 a 8
    do
    {
        n = get_int("height: ");
    }
    while (n < 1 || n > 8);

    //desenhar piramide
    for (int coluna = 0; coluna < n; coluna++)
    {
        for (int s = n - 1 - coluna; s > 0; s--)
        {
            printf(" ");
        }
        for (i = 0; i <= coluna; i++)
        {
            printf("#");
        }
        printf("  ");
        for (j = 0; j <= coluna; j++)
        {
            printf("#");
        }
        printf("\n") ;
    }
}