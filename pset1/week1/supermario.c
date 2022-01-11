#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get positive integer from  user
    int n;
    do
    {
        n = get_int("width: ");
    }
    while (n < 1);
    
    //print as many as n question marks
    for (int i = 0; i < n; i++)
    {
        printf("?\n");
    }
    
}