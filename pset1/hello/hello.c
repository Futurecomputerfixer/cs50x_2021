#include <stdio.h>
#include <cs50.h>

//greet user with the name provided
int main(void)
{
    string name = get_string("what's your name: ");
    printf("hello, %s\n", name);
    
}