/*
* caesar.c
*
* caesar cipher encription
*
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPH 26 // will be used to (% 26) for letters in the alphabet

int
main (int argc, char *argv[])
{
    // test if more or less than 2 arguments are entered
    if (argc != 2)
    {
        // if more or less than 2, yell at user and exit program
        printf("Wrong amount of command line arguments\n");
        return 1;
    }

    // test if argument entered contains a non-digit
    for (int i = 0, ARGV_LEN = strlen(argv[1]); i < ARGV_LEN; i++)
    {
        // if argument contains a non-digit, yell at user and exit program
        if (isdigit(argv[1][i]) == 0)
        {
            printf("%s Contains a non-integer\n", argv[1]);
            return 2;
        }
    }

    // Convert argv to an integer and assign it to variable KEY
    int KEY = atoi(argv[1]);

    // exit program if KEY is negative
    if (KEY < 0)
    {
        // yell at user and exit program
        printf("No Negatives\n");
        return 3;
    }

    // Get plain text string from user
    printf("Enter text to encrypt: ");
    string PLAIN_TEXT = GetString();

	printf("Encryption output: ");
    // loop through the length of the string
    for (int i = 0, PT_CHARS = strlen(PLAIN_TEXT); i < PT_CHARS; i++)
    {
        // check if current char is lowercase
        if (PLAIN_TEXT[i] >= 'a' && PLAIN_TEXT[i] <= 'z')
        {
            // apply caesar cipher
            int CIPHER = (((PLAIN_TEXT[i] - 'a') +
                (KEY % ALPH))  % ALPH) + 'a';

            // print cipher char
            printf("%c", CIPHER);
        }
        // check if current char is uppercase
        else if    (PLAIN_TEXT[i] >= 'A' && PLAIN_TEXT[i] <= 'Z')
        {
        	// apply caesar cipher
            int CIPHER = (((PLAIN_TEXT[i] - 'A') +
                         (KEY % ALPH)) % ALPH) + 'A';

            // print cipher text
            printf("%c", CIPHER);
        }
        // if not an alphabetic char, don't apply caesar cipher
        else
        {
            // print plain text char
            printf("%c", PLAIN_TEXT[i]);
        }
    }

    // final new line for style
    printf("\n");

    // exit program
    return 0;
}
