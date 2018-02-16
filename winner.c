/* winner.c -- win/draw logic
 *
 * defines:
 *
 *   check_winner()
 *
 * Javier Lombillo <javier@asymptotic.org>
 * 2013-04-25
 */

#include <stdlib.h>      // for exit()
#include "tic-tac-toe.h"

extern void delete_board(struct game_board *);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * check_winner()
 * --------------
 * function     : end the game with win or draw
 *              :
 * parameters   : pointer to the game board object, pointer to
 *              : current player object, two ints representing
 *              : most recently selected row and column
 *              :
 * returns      : nothing
 *              :
 * NOTES        : each character on the game board has a numerical
 *              : ASCII value associated with it: 'X' is 88 and 'O'
 *              : is 79. this means that a row full of Xs will have
 *              : a unique sum. these winning sums are pre-calculated
 *              : in init_player() and stored with the player object.
 *              : check_winner() uses loops to inspect the current
 *              : row and column and both diagonals for the winning
 *              : sum; if none is found, it checks for a draw by
 *              : comparing the total number of moves made with the
 *              : maximum number of moves possible.
 */
void check_winner(struct game_board *b, struct player_object *p, int r, int c)
{
    int i, j, sum_r = 0, sum_c = 0, sum_d1 = 0, sum_d2 = 0;

    // check current column for win
    for ( i = 0; i < b->size; i++ )
        sum_c += b->board[i][c];

    // check current row for win
    for ( i = 0; i < b->size; i++ )
        sum_r += b->board[r][i];

    // negative slope diagonal
    for ( i = 0; i < b->size; i++ )
        sum_d1 += b->board[i][i];

    i = 0;
    j = b->size - 1;

    // positive slope diagonal
    while ( i < b->size )
        sum_d2 += b->board[i++][j--];

    if ( (sum_r == p->win)  || (sum_c == p->win) ||
         (sum_d1 == p->win) || (sum_d2 == p->win) )
    {
        printf( "*** Game over! %s wins! *** \n", p->name );
        delete_board( b );
        exit( EXIT_SUCCESS );
    }

    // check for draw
    if ( b->moves == (b->size * b->size) )
    {
        printf( "*** Game Over! Draw. ***\n" );
        delete_board( b );
        exit( EXIT_SUCCESS );
    }

    return;
}
