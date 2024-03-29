/****************************************************************************
 * find.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Prompts user for as many as HAY_MAX values until EOF is reached,
 * then proceeds to search that "haystack" of values for given needle.
 *
 * Usage: find needle
 *
 * where needle is the value to find in a haystack of values
 ***************************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"


// maximum amount of hay
const int HAY_MAX = 65536;


int
main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: %s needle\n", argv[0]);
        return 1;
    }

    // remember needle
    int needle = atoi(argv[1]);

    // fill haystack
    int size;
    int haystack[HAY_MAX];
    for (size = 0; size < HAY_MAX; size++)
    {
        // wait for hay until EOF
        printf("\nhaystack[%d] = ", size);
        int straw = GetInt();
        if (straw == INT_MAX)
            break;

        // add hay to stack
        haystack[size] = straw;
    }
    printf("\n");

    // sort the haystack
    sort(haystack, size);

/* ADDED FOR TESTING!!!!!!!!!!!!!!!!! */
/* ADDED FOR TESTING!!!!!!!!!!!!!!!!! */
    for (int i = 0; i < size; i++)
        printf("\n%d ", haystack[i]);
/* ADDED FOR TESTING!!!!!!!!!!!!!!!!! */
/* ADDED FOR TESTING!!!!!!!!!!!!!!!!! */

    // try to find needle in haystack
    if (search(needle, haystack, size))
        printf("\nFound needle in haystack!\n\n");
    else
        printf("\nDidn't find needle in haystack.\n\n");

    // that's all folks
    return 0;
}
