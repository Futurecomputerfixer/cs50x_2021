#include <stdio.h>
#include <cs50.h>

void stack(int height);

int main(void)
{
    int n ;

    //force user to enter the number within the range
    do
    {
        n = get_int("Height: ");
    }
    while (n > 8 || n < 1);

    stack(n);
}

void stack(int height)
{
    if (height == 0)
    {
        return;
    }

    stack(height - 1);

    for (int i = 0 ;i < height ;i++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0 ;i < height ;i++)
    {
        printf("#");
    }

    printf("\n");
}