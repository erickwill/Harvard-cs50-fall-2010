/**********************
* Skittles
*
* Guess how many skittles
************************/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main()
{
    // seed PRNG
    srand(time(NULL));

    // pick psuedorandom in [0,1023]
    int skittles = rand() % 1024;

    // print skittles #
    // printf("\nHINT %d\n", skittles);

    // boolean test variable
    bool correct = false;

    while (correct == false)
    {
         // ask user to input a guess
         printf("\nGuess how many Skittles are in my jar.\n");
         int guess = GetInt();

        // if wrong guess
        if (skittles != guess)
        {
            printf("\nIncorrect. Try again.\n");
            correct = false;
        }
        else
            correct = true;
    }
    // finish
    printf("\nCorrect! Enjoy your candy!");
}
