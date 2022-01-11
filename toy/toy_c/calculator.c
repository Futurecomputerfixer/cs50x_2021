#include <stdio.h>

int main(void)
{
    int a, b;
    printf("a: ");
    scanf("%i", &a);
    printf("b: ");
    scanf("%i", &b);
    
    
    int c = a * b;
    printf("the result is %i\n", c);
}