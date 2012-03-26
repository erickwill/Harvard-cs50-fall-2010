/****************************************************************************
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int
main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize # infile outfile\n");
        return 1;
    }

    // convert argv[1] to int
    int RESIZE = atoi(argv[1]);

    // RESIZE must be a positive integer <= 100
    if (RESIZE <= 0 || RESIZE > 100) {
        printf("Resize number must be between 1 - 100\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // determine padding for scanlines in original file
    int ogpad =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // store original h/w header values
    int owidth = bi.biWidth;
    int oheight = abs(bi.biHeight);

    // resize h/w header values
    bi.biWidth *= RESIZE;
    bi.biHeight *= RESIZE;

    // determine padding for scanlines in NEW file
    int newpad =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine file/image size header values
    bi.biSizeImage = (bi.biWidth * abs(bi.biHeight) * 3) +
        (abs(bi.biHeight) * newpad);
    bf.bfSize = bi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // initialize scanline buffer
    RGBTRIPLE scanline[bi.biWidth];

    // iterate over infile's scanlines
    for (int ogscan = 0; ogscan < oheight; ogscan++)
    {
        // scanline buffer counter
        int buf_ct = 0;

           // iterate over pixels in scanline
          for (int ogpix = 0; ogpix < owidth; ogpix++)
          {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to scanline buffer
            for (int bufpix  = 0; bufpix < RESIZE; bufpix++, buf_ct++)
                scanline[buf_ct] = triple;
        }

        // skip over padding in original file, if any
        fseek(inptr, ogpad, SEEK_CUR);

        // write scanline buffer to outfile
        for (int wscan = 0; wscan < RESIZE; wscan++) {
            fwrite(&scanline, sizeof(RGBTRIPLE) * bi.biWidth, 1, outptr);

                // write new padding to outfile
                   for (int k = 0; k < newpad; k++)
                       fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
