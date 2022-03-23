// Problem Set 2 - readability
// index = 0.0588 * L - 0.296 * S - 15.8
// L = is the average number of letters per 100 words in the text
// S is the average number of sentences per 100 words in the text
// Using:
// (a) isalpha (count letters)
// (b) isspace (count words)
// (c) ispunct (count sentences)


#include <stdio.h> //printf
#include <cs50.h> //get_string
#include <string.h> //strlen
#include <ctype.h> // isalpha, isspace, ispunct

int count_letters(string texto);
int count_words(string texto);
int count_sentences(string texto);
float index(int letters, int words, int sentences);

int main(void)
{
    // get_string
    string texto = get_string("Texto: ");

    //variables
    int words = 0;
    int sentences = 0;
    int letters = 0;
    float L = 0;
    float S = 0;

    //calculate grade by count letters, words and sentences
    float grade = index(count_letters(texto), count_words(texto), count_sentences(texto));

    //printf based on grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", grade);
    }
}

int count_letters(string texto)
{
    int count = 0;
    for (int i = 0, n = strlen(texto) ; i < n ; i++ )
    {
        if (isalpha(texto[i])){
            count++;
        }
    }
    return count;
}

int count_words(string texto)
{
    int count = 0;
    for (int i = 0, n = strlen(texto) ; i < n ; i++ )
    {
        if (isspace(texto[i])){
            count++;
        }
    }
    return count;
}

int count_sentences(string texto)
{
    int count = 0;
    for (int i = 0, n = strlen(texto) ; i < n ; i++ )
    {
        if (texto[i] == '!' || texto[i] == '.' || texto[i] == '?')
        {
            count++;
        }
    }
    return count;
}

float index(int letters, int words, int sentences)
{
    float index = 0;
    float L = ((float)letters *100)/(words+1);
    float S = ((float)sentences *100)/(words+1);

    index = (0.0588 * L) - (0.296 * S) - 15.8;

    return index;
}
