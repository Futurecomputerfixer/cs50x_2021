#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

//too much work to type printf every time user not cooperate, made a function to shorten it
void eww(void);

//main body
int main(int argc, string argv[])
{
    //first station to check the validity of the key
    //if the key is more than or less than a string of text(i.e a blank), the program stops
    if (argc != 2)
    {
        eww() ;
        return 1;
    }

    //if the input key is not 26 characters, return
    int n = strlen(argv[1]);

    if (n != 26)
    {
        eww();
        return 1;
    }

    //if a character shows up more than once in the key
    for (int i = 0 ; i < n; i++)
    {

        if (isalpha(argv[1][i]) == 0)
        {
            eww();
            return 1;
        }

        for (int x = 0 ; x < i; x++)
        {
            if ((argv[1][i] == argv[1][x]) || (argv[1][i] == argv[1][x] - 32) || (argv[1][i] == argv[1][x] + 32))
            {
                eww();
                return 1;
            }

        }

    }

    //get the original text
    string text = get_string("plaintext: ");
    int y = strlen(text);
    //to encrypt it with the key provided
    for (int i, j = 0 ; j < y; j++)
    {
        if (isupper(text[j]) && text[j]== argv[1][i])
        {
            text[j] = "A" + i;
            text[j] = toupper(text[j]);
        }
        else if (islower(text[j]))
        {
            text[j]  = argv[1][text[j] - 97];
            text[j] = tolower(text[j]);
        }

    }

    //present the secret code, Woo-hoo
    printf("ciphertext: %s\n", text);




}


//the function
void eww(void)
{
    printf("Please enter a correct key (26 distinct letters)\n") ;

}