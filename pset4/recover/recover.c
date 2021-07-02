#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCKSIZE = 512;
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: filter image\n");
        return 1;
    }

    // Open image file
    char *image_filename = argv[1];
    FILE *inptr = fopen(image_filename, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", image_filename);
        return 1;
    }

    BYTE buffer[BLOCKSIZE * sizeof(BYTE)];
    int nread = fread(buffer, sizeof(BYTE), BLOCKSIZE, inptr);
    int JPEG_num = 0;
    char JPEG_filename[8];
    FILE *outptr = NULL;
    while (nread != 0)
    {

        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff 
            && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not first JPEG
            if (JPEG_num != 0)
            {
                // close last file
                fclose(outptr);
            }

            // open new file to write
            sprintf(JPEG_filename, "%03i.jpg", JPEG_num);
            outptr = fopen(JPEG_filename, "w");
            // write to file
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, outptr);
            JPEG_num++;
        }
        else
        {
            // Continue writing to file
            if (JPEG_num != 0)
            {
                fwrite(buffer, sizeof(BYTE), BLOCKSIZE, outptr);
            }
        }
        nread = fread(buffer, sizeof(BYTE), BLOCKSIZE, inptr);
    }




    // Close image file
    fclose(inptr);
    return 0;

}