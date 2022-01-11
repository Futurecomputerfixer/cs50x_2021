#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long x = get_long("what is x:");

    long y = get_long("what is y:");

    printf("%li\n", x * y); 
}