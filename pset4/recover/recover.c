#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check if executed correctly
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    //check if segmentation fault
    if (card == NULL)
    {
        printf("Usage: ./recover1111111111 image\n");
        return 1;
    }

    int count = 0;
    BYTE buffer[512];
    char filename[8];
    FILE *img;

    //check end of the file
    while (fread(buffer, sizeof(buffer), 1, card) == 1)
    {
        //check if it is a JPG begin
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close if it is not the first
            if (count > 0)
            {
                fclose(img);
            }

            //open a new one and record buffer
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;
            fwrite(buffer, sizeof(buffer), 1, img);
        }
        //record buffer
        else if (count > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }

    }
    //close files
    fclose(img);
    fclose(card);

}
