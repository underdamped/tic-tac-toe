/* board.c -- board-specific routines
 *
 * defines:
 *
 *   show_board()
 *   delete_board()
 *
 * Javier Lombillo <javier@asymptotic.org>
 * 2013-04-25
 */

#include <stdlib.h>      // for free()
#include "tic-tac-toe.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * show_board()
 * --------------
 * function     : prints to the screen an ASCII representation
 *              : of the board's current state
 *              :
 * parameters   : pointer to the game board object
 *              :
 * returns      : nothing
 */
void show_board(struct game_board *b)
{
    int i, j;

    puts( "Current game:" );
    puts( "-------------" );

    for ( i = 0; i < b->size; i++ )
    {
        for ( j = 0; j < b->size; j++ )
            printf( " %c ", b->board[i][j] );
        puts("");
    }

    puts( "" );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * delete_board()
 * --------------
 * function     : clean up our mess
 *              :
 * parameters   : pointer to the game board object
 *              :
 * returns      : nothing
 */
void delete_board(struct game_board *b)
{
    // release the board storage
    free( b->board[0] );

    // release the row-pointer storage
    free( b->board );
}
