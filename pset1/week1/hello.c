#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //greet user
    string answer = get_string("what's your name? ");
    printf("hello, %s\n", answer);
}