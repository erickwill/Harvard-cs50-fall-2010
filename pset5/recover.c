/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Searches and writes out jpg files from card.raw
 ***************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

typedef uint8_t BYTE;

BYTE buffer[BLOCK];

int
main(int argc, char *argv[])
{

    // jpg filename counter
    int filect = 0;
    // jpg filename
    char name[13];
    // track if writing to file
    int writing = 0;

    // open input file
    FILE *raw = fopen("./card.raw", "r");
    if (raw == NULL) {
        printf("Could not open card.raw\n");
        return 1;
    }

    // create jpg
    sprintf(name, "./jpg/%.3d.jpg", filect);
    FILE *jpg = fopen(name, "w");
    if (jpg == NULL) {
        printf("Could not open %.3d.jpg\n", filect);
        return 2;
    }

    // check for end of file signal
    while(feof(raw) == 0) {

        // read data block to buffer
        fread(buffer, sizeof(BYTE), BLOCK, raw);

        // test first 4 bytes of block for jpg header
        if (buffer[0] == 0xFF && 
            buffer[1] == 0xD8 && 
            buffer[2] == 0xFF &&
            (buffer[3] == 0xE0 || buffer[3] == 0xE1)) {

            // close last jpg and start writing next file
            if (writing == 1) {
                fclose(jpg);
                filect++;
            }

            if (writing !=0) {
                // create jpg
                sprintf(name, "./jpg/%.3d.jpg", filect);
                FILE *jpg = fopen(name, "w");
                if (jpg == NULL) {
                    printf("Could not open ./jpg/%.3d.jpg\n", filect);
                    return 2;
                }
            }
            // track writing next block
            writing = 1;

        }
            // write buffer to outfile
            fwrite(buffer, sizeof(BYTE), BLOCK, jpg);
    }

    // close files
    fclose(jpg);
    fclose(raw);

    return 0;

}
