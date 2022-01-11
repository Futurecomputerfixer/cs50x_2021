#include <time.h>
#include <stdio.h>

int main(void)
{
    printf("The Time is %li.\n", time(0) % 60);
}