/*
* oldman.c
*
* Prints the "This Old Man" song
*
*/

#include <stdio.h>

int main (void)
{
    // declare arrays for verse iteration and lyrics
    char *song_number[10] =
        {"one","two","three","four","five", "six",
        "seven","eight","nine","ten"};
    char *lyric[10] =
        {"thumb","shoe","knee","door","hive","sticks",
        "heaven","gate","spine","again"};

    // iterate verses with conditions for different lyrics
    for (int i = 0; i < 10; i++)
    {
        // all verses will print this
        printf("\nThis old man, he played %s\n", song_number[i]);
        printf("He played knick-knack ");

            // all but 2 verses will print this
            if (i != 6 && i !=9)
                printf("on my %s\n", lyric[i]);

            // verse 7 needs a different lyric
            else if (i == 6)
                printf("up in %s\n", lyric[i]);

            // verse 10 needs a different lyric too
            else
                printf("once %s\n", lyric[i]);

    // finish up the verse
    printf("Knick-knack paddywhack, give your dog a bone\n");
    printf("This old man came rolling home\n");
    }

    return 0;
}
