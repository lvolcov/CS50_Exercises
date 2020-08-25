#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check1
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check2
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char key[26];

    //convert all to lower
    for (int i = 0 ; i < 26 ; i++)
    {
        //printf("%c", argv[1][i]);
        if (isupper(argv[1][i]))
        {
            key[i] = argv[1][i] + 32;
        }
        else
        {
            key[i] = argv[1][i];
        }
    }

    //check3
    for (int i = 0 ; i < 26 ; i++)
    {
        for (int x = i + 1 ; x < 26 ; x++)
        {
            if (key[i] == key[x] || !isalpha(key[i]))
            {
                printf("Key must contain 26 unique characters.\n");
                return 1;
            }
        }
    }

    //get plain
    string plain = get_string("plaintext:  ");
    int lenght = strlen(plain);

    //convert
    printf("ciphertext: ");
    for (int i = 0; i < lenght ; i++)
    {
        if (isupper(plain[i]))
        {
            printf("%c", toupper(key[(int)plain[i] - 65]));
        }
        else if (islower(plain[i]))
        {
            printf("%c", key[(int)plain[i] - 97]);
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
}