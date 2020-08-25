#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

//declare functions
int count_letters(string text, int size);
int count_words(string text, int size);
int count_sentences(string text, int size);

//main function
int main(void)
{
    string text =  get_string("Text: ");
    int size = 0;

    //count lenght of text
    for (int i = 0; text[i] != '\0'; i++)
    {
        size++;
    }
    // call functions
    int letters = count_letters(text, size);
    int words = count_words(text, size);
    int sentences = count_sentences(text, size);

    // calc index
    double index = 0.0588 * ((double) letters / (double) words * 100) - 0.296 * ((double) sentences / (double) words * 100) - 15.8;
    index = round(index);

    //print answer
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
    //printf ("%i letter(s)\n", letters);
    //printf ("%i word(s)\n", words);
    //printf ("%i sentences(s)\n", sentences);
    //printf ("%f index\n", index);
}

//Count letters
int count_letters(string text, int size)
{
    int count = 0;
    for (int i = 0; i < size ; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

//Count words
int count_words(string text, int size)
{
    int count = 1;
    for (int i = 0; i < size ; i++)
    {
        if (isblank(text[i]))
        {
            count++;
        }
    }
    return count;
}

//count sentences
int count_sentences(string text, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}