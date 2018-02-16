/* init.c -- initialization routines
 *
 * defines:
 *
 *   init_board()
 *   init_players()
 *
 * Javier Lombillo <javier@asymptotic.org>
 * 2013-04-25
 */

#include <stdlib.h>      // malloc() and rand()
#include <string.h>      // strcpy()
#include "tic-tac-toe.h"

extern int human_move(struct game_board *, struct player_object *);
extern int cpu_move(struct game_board *, struct player_object *);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * init_board()
 * --------------
 * function     : creates an MxM matrix suitable for a
 *              : tic-tac-toe board
 *              :
 * parameters   : pointer to the game board object, an int
 *              : representing the desired size of the matrix
 *              :
 * returns      : 0 on success, -1 on failure
 */
int init_board(struct game_board *b, int size)
{
    int i, j;

    // build a 2D array dynamically
    b->size = size;
    b->board = malloc( b->size * sizeof(int*) );

    if ( b->board == NULL )
    {
        puts( "[ERROR] Memory allocation error, aborting." );
        return -1;
    }

    for ( i = 0; i < b->size; i++ )
    {
        b->board[i] = malloc( b->size * sizeof(int*) );

        if ( b->board[i] == NULL )
        {
            puts( "[ERROR] Memory allocation error, aborting." );
            return -1;
        }

        for ( j = 0; j < b->size; j++ )
            b->board[i][j] = '-';
    }

    b->moves = 0;

    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * init_players()
 * --------------
 * function     : creates and assigns two player objects
 *              :
 * parameters   : pointer to an array of player objects, two ints
 *              : representing the number of human players and the
 *              : size of the board 
 *              :
 * returns      : 0 on success, -1 on failure
 *              :
 * NOTES        : every game has two player objects, p[0] and p[1].
 *              : p[0] is always X and so always goes first;
 *              : p[1] is always O. we assign the human and/or cpu
 *              : players to the player objects randomly, which ensures
 *              : everyone gets a chance to play as X.
 */
int init_players(struct player_object *p, int num, int size)
{
    int coin;
    char name1[32], name2[32];

    if ( num < 1 || num > 2 )
    {
        puts( "Invalid choice!" );
        return -1;
    }

    printf( "Player 1, enter your name: " );

    if ( scanf("%31s", name1) != 1 )
    {
        puts( "Invalid name." );
        return -1;
    }

    if ( num == 1 )
    {
        printf( "\n\nGreetings, %s, you will play against "
                "the computer.\n", name1 );
        strcpy( name2, "COMPUTER" );
    }
    else
    {
        printf( "Player 2, enter your name: " );

        if ( scanf("%31s", name2) != 1 )
        {
            puts( "Invalid name." );
            return -1;
        }
    }

    p[0].mark = 'X'; // X always goes first
    p[1].mark = 'O';

    // winner is determined numerically (see check_winner() function)
    p[0].win  = size * 'X';
    p[1].win  = size * 'O';

    // we randomly assign players to the player objects
    coin = rand() % 2;

    if ( coin == 0 ) // human is X
    {
        strcpy( p[0].name, name1 );
        p[0].move_func = (void *)&human_move;

        strcpy( p[1].name, name2 );
        p[1].move_func = (num == 1)
            ? (void *)&cpu_move
            : (void *)&human_move;
    }
    else // human is O
    {
        strcpy( p[0].name, name2 );
        p[0].move_func = (num == 1)
            ? (void *)&cpu_move
            : (void *)&human_move;

        strcpy( p[1].name, name1 );
        p[1].move_func = (void *)&human_move;
    }

    // let everyone know what is going on
    printf( "Players:\n"
            "\t%s is X and will move first\n"
            "\t%s is O and will move second\n", p[0].name, p[1].name);

    return 0;
}
