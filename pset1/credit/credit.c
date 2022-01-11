#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //get number from user
    long n = get_long("Number: ");

    //set up variables
    long b, d, f;
    long e = 0;
    long g = 0;
    int h = 1;


    //get the first two digits of the number to
    //quickly determine what kind of card that is
    for (long a = 10; a < n ; a *= 10)
    {
        b = (10 * n) / a;
        h++;
    }


    //apply the  step of algorithm
    for (long y = 1; y < n ; y *= 100)
    {
        d = ((n % (10 * y)) / y);
        e = e + d ;
    }

    for (long x = 10; x < n; x *= 100)
    {
        f = ((n % (10 * x)) / x);

        if ((2 * f) >= 10)
        {
            g = g + ((2 * f) % 10) + (1);
        }

        else
        {
            g = g + (2 * f);
        }
    }

    int z = ((e + g) % 10);


    //algorithm step two, print out the output

    //the very first is to use Luhn’s Algorithm
    if (z != 0)
    {
        printf("INVALID\n");
    }

    //even if the number passes the algorithm evaluation,

    //the number may be more or less digits than valid card number
    else if ((h != 13) && (h != 15) && (h != 16))
    {
        printf("INVALID\n");
    }

    //it may still be invalid depending on the starting digits
    else if (b == 34)
    {
        printf("AMEX\n");
    }

    else if (b == 37)
    {
        printf("AMEX\n") ;
    }

    else if ((50 < b) && (b < 56))
    {
        printf("MASTERCARD\n");
    }

    else if ((39 < b) && (b < 50))
    {
        printf("VISA\n");
    }

    //those numbers not begins with
    //the valid card number starter would be counted as invalid
    else
    {
        printf("INVALID\n");
    }


}