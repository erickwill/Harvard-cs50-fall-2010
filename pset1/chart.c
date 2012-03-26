/*
* Chart.c
* cs50
* pset1
*
* Chart isawyouharvard.com
*
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    // declare variables
    int mspf, fspm, fspf, mspm;

    // get non-negative M spotting F
    do
    {
        printf("\nM spotting F:");
        mspf = GetInt();
            if (mspf < 0)
                printf("\nNo negative answers. Try again.\n");
    }
    while (mspf < 0);

    // get non-negative F spotting M
    do
    {
        printf("F spotting M:");
        fspm = GetInt();
            if (fspm < 0)
                printf("\nNo negative answers. Try again.\n");
    }
    while (fspm < 0);

    // get non-negative F spotting F
    do
    {
        printf("F spotting F:");
        fspf = GetInt();
            if (fspf < 0)
                printf("\nNo negative answers. Try again.\n");
    }
    while (fspf < 0);

    // get non-negative M spotting M
    do
    {
        printf("M spotting M:");
        mspm = GetInt();
            if (mspm < 0)
                printf("\nNo negative answers. Try again.\n");
    }
    while (mspm < 0);

    // calculate percentages of each input for graph output
    int totanswers = (mspf + fspm + fspf + mspm);

    float percmspf = mspf / (float)totanswers;

    float percfspm = fspm / (float)totanswers;

    float percfspf = fspf / (float)totanswers;

    float percmspm = mspm / (float)totanswers;

    // calculate how many # to print
    int lengthmspf = percmspf * 80;

    int lengthfspm = percfspm * 80;

    int lengthfspf = percfspf * 80;

    int lengthmspm = percmspm * 80;

    // print graph
    printf("\nWho is Spotting Whom\n");

    printf("\nM spotting F\n");
    for (int i = 0; i < lengthmspf; i++)
        printf("#");

    printf("\nF spotting M\n");
    for (int j = 0; j < lengthfspm; j++)
        printf("#");

    printf("\nF spotting F\n");
    for (int k = 0; k < lengthfspf; k++)
        printf("#");

    printf("\nM spotting M\n");
    for (int x = 0; x < lengthmspm; x++)
        printf("#");

    // new line at the end for style
    printf("\n");

    return 0;
}
