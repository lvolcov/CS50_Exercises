#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check 1
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //check 2
    for (int i = 0; argv[1][i] != '\0' ; i++)
    {
        if (!(isdigit(argv[1][i])))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //convert key
    int k = atoi(argv[1]);

    //Get plain text
    string plain = get_string("plaintext:  ");
    int lenght = strlen(plain);

    //convert and print
    char cipher[lenght];

    printf("ciphertext: ");
    for (int i = 0; i < lenght ; i++)
    {
        if (isupper(plain[i]))
        {
            printf("%c", (65 + (((int)plain[i] - 65 + k) % 26)));
        }
        else if (islower(plain[i]))
        {
            printf("%c", (97 + (((int)plain[i] - 97 + k) % 26)));
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
}