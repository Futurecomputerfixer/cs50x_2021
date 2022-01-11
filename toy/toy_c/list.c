#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    node *list = NULL;
    int i, j;
    scanf("%i", &i);
    scanf("%i", &j);
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = i * j;
    n->next = NULL;

    list = n;
    printf("%i\n", (*n).number);
}