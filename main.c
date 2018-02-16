/* main.c -- tic-tac-toe
 *
 * term project for COP2270, "C for Engineers" (Prof. Lahlou)
 * 
 * Javier Lombillo <javier@asymptotic.org>
 * 2013-04-25
 */

#include <stdlib.h>
#include <time.h>
#include "tic-tac-toe.h"

extern int init_board(struct game_board *, int);
extern int init_players(struct player_object *, int, int);
extern void delete_board(struct game_board *);
extern void run_intro(int *, int *);
extern void show_help(void);

int main(void)
{
    int i, *ps, *pp, result, board_size, num_players;
    struct game_board matrix, *pm;
    struct player_object players[2];

    srand( time(NULL) ); // seed for random first player

    ps = &board_size;
    pp = &num_players;
    pm = &matrix;

    run_intro( ps, pp );

    result = init_board( pm, board_size );

    if ( result < 0 )
    {
        puts( "Please try again with a smaller board." );
        exit( EXIT_FAILURE );
    }

    result = init_players( players, num_players, board_size );

    if ( result < 0 )
    {
        delete_board( pm );
        exit( EXIT_FAILURE );
    }

    printf( "\n\n*** Press Enter key to play a %d-player %dx%d game! ***",
            num_players, board_size, board_size );

    getchar();
    getchar(); // 2nd one is to eat the newline

    while ( 1 )
    {
        // the outer for() selects the player; the inner while() loops
        // until the current player makes a valid move ("continue" is
        // unnecessary but aesthetically pleasing)
        for ( i = 0; i < 2; i++ )
            while ( players[i].move_func(pm, &players[i]) < 0 )
                continue;
    }

    // this is never reached, but it makes the compiler happy
    return 0;
}
