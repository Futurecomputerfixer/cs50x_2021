#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;
bool jpg(uint8_t array[]);
int main(int argc, char *argv[])
{
    //check if input is correct
    if (argc != 2)
    {
        printf("Usage: ./recover image");
    }

    //check if the memory card exists
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf(" Could not open file.\n");
        return 1;
    }

    uint8_t buffer [BLOCK_SIZE];
    int counter = 1;
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card))
    {

        while (jpg(buffer) == true)
        {   
            //the first image recovered
            if (counter == 1)
            {
                FILE *file = fopen("000.jpg", "w");
                do
                {
                    fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, file);
                    fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card);
                }
                while (jpg(buffer) != true);
                fclose(file);
                counter++;
            }

            else
            {
                int x = counter - 1;
                char *f = malloc(8);
                if (f == NULL)
                {
                    return 1;
                }

                sprintf(f, "%03i.jpg", x);

                FILE *img = fopen(f, "w");

                do
                {
                    fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
                    if (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card) == 0)
                    {
                        return 0;
                    };
                }
                while (jpg(buffer) != true);

                fclose(img);
                free(f);
                counter++;


            }
        }



    }

    fclose(card);





}


bool jpg(uint8_t array[])
{
    if (array[0] == 0xff && array[1] == 0xd8 && array[2] == 0xff && (array[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}