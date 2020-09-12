#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// function declarations
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);


    float letter_formula = (float)letters / (float)words * 100;
    float sentences_formula = (float)sentences / (float)words * 100;
    int grade = round((0.0588 * letter_formula) - (0.296 * sentences_formula) - 15.8);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
    return 0;
}


/*
    function used to count letters from a sentence

    input - string (comes from cs50 library, else would be an array of chars)
    returns - int (the total count of letters found)
*/
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

/*
    function to count words
    input - string (comes from cs50 library, else would be an array of chars)
    returns - int (the total count of words found)
*/
int count_words(string text)
{
    int words = 0;

    if (text[0] != ' ')
    {
        words += 1;
    }

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            words += 1;
        }
    }

    return words;
}

/*
    input - string (comes from cs50 library, else would be an array of chars)
    returns - int (the total count of sentences found)
*/
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }

    return sentences;
}