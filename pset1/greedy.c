/*
* Time For Change
*
* Greedy Algorithm Example
* CS50 pset1
*
*/

#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float i;
    do
    {
    // get amount for change from user
    printf("\nHow much change are you owed?\n");
    i = GetFloat();
        // no negative responses
        if (i < 0)
            printf("\nDon't be negative.");
    }
    // keep asking until positive
    while (i < 0);

    // round float and cast to int
    int j = round(i * 100);
    printf("Your entry = %d cents\n", j);

    // calculate change
    int quarters = (j / 25);
    printf("Quarters = %d, ", quarters);

    int dimes = ((j - (quarters * 25)) / 10);
    printf("Dimes = %d, ", dimes);

    int nickels = ((j - ((quarters * 25) + (dimes * 10))) / 5);
    printf("Nickels = %d, ", nickels);

    int pennies = ((j - ((quarters * 25) + (dimes * 10) + (nickels * 5))) / 1);
    printf("Pennies = %d\n", pennies);

    // print total coins
    int k = (quarters + dimes + nickels + pennies);
        if (k > 1000)
            printf("\nHope you brought something to carry these in ;)\n ");

    printf("Total coins = %d\n", k);

    return 0;
}
