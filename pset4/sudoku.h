/****************************************************************************
 * sudoku.h
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Compile-time options for the game of Sudoku.
 ***************************************************************************/

// game's author
#define AUTHOR "CS50"

// game's title
#define TITLE "Sudoku"

// banner's colors
#define FG_BANNER COLOR_GREEN
#define BG_BANNER COLOR_BLACK

// grid's colors
#define FG_GRID COLOR_CYAN
#define BG_GRID COLOR_BLACK

// border's colors
#define FG_BORDER COLOR_BLACK
#define BG_BORDER COLOR_CYAN

// logo's colors
#define FG_LOGO COLOR_YELLOW
#define BG_LOGO COLOR_BLACK

// nicknames for pairs of colors
enum { PAIR_BANNER = 1, PAIR_GRID, PAIR_BORDER, PAIR_LOGO};
