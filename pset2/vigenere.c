/*
* vigenere.c
*
* CS50
*
* encrypt input text with vigenere cipher
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // check if there are exactly two args from command line
    if (argc == 2)
    {
        // loop through arg string
        for (int i = 0, LEN = strlen(argv[1]); i < LEN; i++)
        {
            // ensure args are only alphabetic characters
            if (isalpha(argv[1][i]) == 0)
            {
                // yell at user and exit if not
                printf("\nInvalid command line argument (%c)\n", argv[1][i]);
                return 2;
            }
        }
    }

    else
    {
        // yell at user and exit if incorrect amount of args at command line
        printf("\nIncorrect amount of command line arguments\n");
        return 1;
    }

    // pass command line arg to string KEY
    string KEY = argv[1];
    // get plain text from user to encrypt
    printf("Enter text to encrypt: ");
    string PTXT = GetString();

    // counter for KEY string
    int j = 0;
    // value to encrypt by
    int KEYSET;
    // pass plain text to cipher txt variable
    string CTXT = PTXT;

	printf("Encrypted output: ");

    // loop through plain text
    for (int i = 0, PLEN = strlen(PTXT); i < PLEN; i++)
    {
        // if not an alphabetic character,
        // don't encrypt and don't advance KEY counter
        if (isalpha(PTXT[i]) == 0)
            CTXT[i] = PTXT[i];

        else
        {
            // adjust KEY value if upper or lower case
            if (isupper(KEY[j]) != 0)
                KEYSET = (int)KEY[j] - 'A';
            else
                KEYSET = (int)KEY[j] - 'a';

            // apply cipher if uppercase
            if (isupper(PTXT[i]) != 0)
                CTXT[i] = (((PTXT[i] - 'A') + KEYSET) % 26 + 'A');
            // apply cipher if lowercase
            if (islower(PTXT[i]) != 0)
                CTXT[i] = (((PTXT[i] - 'a') + KEYSET) % 26 + 'a');

            // loop around KEY string
            if (j < strlen(KEY) -1)
                j++;
            else
                j = 0;
        }

    // print cipher
    printf("%c", CTXT[i]);

    }

    // add new line after finished cipher for style
    printf("\n");

    // exit finished program
    return 0;
}
