/* moves.c -- gameplay routines
 *
 * defines:
 *
 *   human_move()
 *   cpu_move()
 *
 * Javier Lombillo <javier@asymptotic.org>
 * 2013-04-25
 */

#include <stdlib.h>      // for rand()
#include "tic-tac-toe.h"

extern void check_winner(struct game_board *, struct player_object *, int, int);
extern void show_board(struct game_board *);
extern void delete_board(struct game_board *);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * human_move()
 * --------------
 * function     : handle game move for human players
 *              :
 * parameters   : pointer to the game board object, pointer to
 *              : the appropriate human player object
 *              :
 * returns      : 0 on success, -1 on failure
 */
int human_move(struct game_board *b, struct player_object *p)
{
    char buff[32];
    int row = 0, col = 0;
    static int first_move = 1;

    // show board if we're the first player and this is our first move
    if ( first_move && (p->mark == 'X') )
    {
        show_board( b );
        first_move = 0;
    }

    printf( "[%s (%c)] Enter move as 'row, column': ",
            p->name, p->mark );

    if ( fgets(buff, sizeof buff, stdin) == NULL )
    {
        puts( "MURDER, SHE WROTE!" );
        return -1;
    }
    else if ( buff[0] == 'q' )
    {
        puts( "Goodbye.\n" );
        delete_board( b );
        exit( 0 );
    }
    else if ( sscanf(buff, "%d, %d", &row, &col) != 2 )
    {
        puts( "Unrecognized input, please enter 2,1 to indicate second column, first row." );
        return -1;
    }

    // C arrays are zero-indexed, humans like to start at 1
    row--;
    col--;

    if ( ((row > b->size - 1) || (col > b->size - 1)) ||
         ((row < 0) || (col < 0)) )
    {
        puts( "Illegal move: outside the board, try again!" );
        return -1;
    }

    if ( b->board[row][col] != '-' )
    {
        puts( "Illegal move: spot taken, try again!" );
        return -1;
    }

    b->board[row][col] = p->mark;
    b->moves++;

    show_board( b );
    check_winner( b, p, row, col );

    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * cpu_move()
 * --------------
 * function     : handle game move for computer player
 *              :
 * parameters   : pointer to the game board object, pointer to
 *              : the computer player object
 *              :
 * returns      : 0 on success, -1 on failure
 */
int cpu_move(struct game_board *b, struct player_object *p)
{
    int row, col;

    // AI: pick random row/col between 0 and (size - 1)
    row = rand() % b->size;
    col = rand() % b->size;

    if ( b->board[row][col] != '-' )
        return -1;

    b->board[row][col] = p->mark;
    b->moves++;

    printf( "[COMPUTER (%c)] I've made my move.\n", p->mark );

    show_board( b );
    check_winner( b, p, row, col );

    return 0;
}
