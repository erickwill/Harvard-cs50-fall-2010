/****************************************************************************
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 ***************************************************************************/

#include <cs50.h>

#include "helpers.h"


/*
 * Returns true if value is in array of n values, else false.
 */

bool
search(int value, int array[], int n)
{
    // set boundries
    int low = 0;
    int high = n - 1;

    // don't overlap high/low values
    while (low <= high)
    {
        // find center
        int center = (low + high) / 2;

        // return true on success
        if (array[center] == value)
            return true;
        // recalibrate center to search upper half
        else if (array[center] < value)
            low = center + 1;
        // recalibrate center to search lower half
           else
            high = center - 1;
    }
    // not found
    return false;
}


/*
 * Sorts array of n values.
 */

void
sort(int values[], int n)
{
    // implement an O(n^2) sort
    // loop through array
    for (int i = 0; i < n - 1; i++)
    {
        // bool to break out of swap loop
        int swap = 0;

        // swap loop
        for (int j = 0; j < n - 1; j++)
        {
            // swap integers
            if (values[j] > values[j + 1])
            {
                // create pointer to array
                int *ptarr = &values[j];
                // pointer to next value in array
                int *ptarr2 = ptarr + 1;
                // temp storage for swap
                int tmp = *ptarr;
                // do the swap
                *ptarr = *ptarr2;
                *ptarr2 = tmp;
                // count swaps made
                swap++;

            }
        }

    // if no swaps, done
    if (swap == 0)
        break;
    }

    return;
}

