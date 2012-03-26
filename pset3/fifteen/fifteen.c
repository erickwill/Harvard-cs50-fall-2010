/***************************************************************************
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements The Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 ***************************************************************************/

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);


int
main(int argc, char *argv[])
{
    // greet user with instructions
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: %s d\n", argv[0]);
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %d x %d and %d x %d, inclusive.\n",
         DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}


/*
 * Clears screen using ANSI escape sequences.
 */

void
clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}


/*
 * Greets player.
 */

void
greet(void)
{
    clear();
    printf("WELCOME TO THE GAME OF FIFTEEN\n");

    usleep(2000000);
}


/*
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */

void
init(void)
{
    // fill 2d array with tiles value "99"
    // makes checking for win easier later
    for (int i = 0; i < DIM_MAX; i++)
    {
        for(int j = 0; j < DIM_MAX; j++)
        {
            board[i][j] = 99;
        }
    }

    // highest tile value
    int topval = d * d - 1;

    // fill 2d array with decreasing tile values
    for (int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            board[i][j] = topval;
            topval--;
        }
    }

    // assign blank space "99"
    board[d-1][d-1] = 99;

    // if board dimension is even, swap "1" & "2" tiles
    if (d % 2 == 0)
    {
        int* swaphigh = &board[d-1][d-2];
        int* swaplow = &board[d-1][d-3];
        int tmp = *swaplow;
        *swaplow = *swaphigh;
        *swaphigh = tmp;
    }
}


/*
 * Prints the board in its current state.
 */

void
draw(void)
{

    for (int i = 0; i < d; i++)
       {
           for(int j = 0; j < d; j++)
           {
               // don't print empty tile for now
               if (board[i][j] != 99)
            {
                // print tiles that contain values
                printf("%2d ", board[i][j]);

                // print new line at end of row
                if (j == d - 1)
                    printf("\n");
            }
            // print empty tile; print new line if empty tile is at row end
            else if (j == d - 1)
                printf("%2c\n", 95);
            else
                printf("%2c ", 95);
        }
    }
}


/*
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */

bool
move(int tile)
{
    // tile position in board
    int ROW, COL;

    // bool for found tile
    int found = 0;

    // return false if user selects "99"
    if (tile == 99)
    {
        printf("\n99 not found on board!\n");
        return false;
    }

    // search through board; if tile found, log position
    for (int i = 0; i < d; i++)
       {
           for (int j = 0; j < d; j++)
           {
               if (board[i][j] == tile)
               {
                   found = 1;
                   ROW = i;
                   COL = j;
               }
           }
       }

    // return false if tile doesn't exist
    if (found == 0)
    {
        printf("\n%d not found on board!\n", tile);
        return false;
    }

    // if move is valid, swap tiles
    if (ROW > 0)
    {
        if (board[ROW-1][COL] == 99)
        {
            int* CURRENT = &board[ROW][COL];
            int* SWAP = &board[ROW-1][COL];
            int tmp = *CURRENT;
            *CURRENT = *SWAP;
            *SWAP = tmp;
            return true;
        }
    }

    if (ROW < d-1)
    {
        if (board[ROW+1][COL] == 99)
        {
            int* CURRENT = &board[ROW][COL];
            int* SWAP = &board[ROW+1][COL];
            int tmp = *CURRENT;
            *CURRENT = *SWAP;
            *SWAP = tmp;
            return true;
        }
    }

    if (COL > 0)
    {
        if (board[ROW][COL-1] == 99)
        {
            int* CURRENT = &board[ROW][COL];
            int* SWAP = &board[ROW][COL-1];
            int tmp = *CURRENT;
            *CURRENT = *SWAP;
            *SWAP = tmp;
            return true;
        }
    }

    if (COL < d-1)
    {
        if (board[ROW][COL+1] == 99)
        {
            int* CURRENT = &board[ROW][COL];
            int* SWAP = &board[ROW][COL+1];
            int tmp = *CURRENT;
            *CURRENT = *SWAP;
            *SWAP = tmp;
            return true;
        }
    }

    // illegal move
    return false;
}

/*

 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */

bool
won(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            int* ptr = &board[i][j];
            int* ptr2 = ptr + 1;
            if (*ptr > *ptr2)
                return false;
        }
    }

    return true;
}
