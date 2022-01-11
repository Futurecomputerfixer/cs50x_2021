#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//create functions to make my main codes more succinct
long count_letters(string setence);
long count_words(string text);
long count_sentences(string q);
int CL_index(long a1, long a2, long a3);


//the main function. MANUALLY HIGHLIGHTING
int main(void)
{

    //text inputs
    string n = get_string("Text: ");
    //get basic data from input
    long a = count_letters(n);
    long b = count_words(n);
    long c = count_sentences(n);

    //apply Coleman-Liau index
    int d = CL_index(a, b, c);

    //still there are some exception other than grade#
    if (d > 15)
    {
        printf("Grade 16+\n");
    }
    else if (d < 1)
    {
        printf("Before Grade 1\n");
    }

    //normalized again, whew!
    else
    {
        printf("Grade %i\n", d);
    }

}




//customize the first function, to get the letters counts
long count_letters(string sentence)
{
    long l = 0;
    for (long i = 0, j = strlen(sentence); i < j; i++)
    {
        if (('a' <=  sentence[i] && sentence[i] <= 'z') || ('A' <= sentence[i] && sentence[i] <= 'Z'))
        {
            l++;
        }
    }
    return l;

}

//customize the second function, to get the words counts
long count_words(string text)
{
    long m = 1;
    for (long n = 0, o = strlen(text); n <= o; n++)
    {
        if (o == 0)
        {
            m--;
        }
        else (text[n] == ' ')
        {
            m++;
        }
        
    }
    return m;
}

//customize the thrid function, to get the sentences counts
long count_sentences(string q)
{
    long x = 0;
    for (long r = 0, s = strlen(q); r < s; r++)
    {
        if (q[r] == '.' || q[r] == '?' || q[r] == '!')
        {
            x++;
        }
    }

    return x ;

}

//customize the last function, to run the index algorithm
int CL_index(long a1, long a2, long a3)
{

    float L = (float)a1 / ((float)a2 / 100);
    float S = (float)a3 / ((float)a2 / 100);
    float A = 0.0588 * L - 0.296 * S - 15.8;
    int B = round(A);
    return B;
}