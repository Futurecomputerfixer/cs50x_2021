#include <cs50.h>
#include <stdio.h>

void stack(int h);

int main(void)
{
    int height = get_int("height: ");
    if (height == 0)
    {
        printf ("ERROR:input has to be greater than 0\n");
        return 1;
    }
    stack(height);
}

void stack(int h)
{
   if (h == 0)
   {
       return;
   }
   stack(h - 1);
   for (int i = 0 ;i < h ;i++)
   {
       printf("#");
   }
   printf("\n");
}