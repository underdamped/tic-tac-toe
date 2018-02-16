/* help.c -- help the user setup a game
 *
 * defines:
 *
 *   show_help()
 *   run_intro()
 *
 * Javier Lombillo <javier@asymptotic.org>
 * 2013-04-25
 */

#include <stdio.h>
#include <string.h>  // strcmp()

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * show_help()
 * --------------
 * function     : prints to the screen a help message
 *              :
 * parameters   : none
 *              :
 * returns      : nothing
 */
void show_help(void)
{
    puts( "\n\nInstructions\n"
          "------------\n"
          "Enter moves in \"m,n\" format, where m is the row and n\n"
          "is the column. For example, to place a mark on the top\n"
          "left cell you would type\n\n\t1,1\n\nThe first player will "
          "be chosen randomly.\n" 
          "Once the game has started, you may enter 'q' to quit.\n");

    printf( "Press Enter key to continue: " );
    getchar();
    getchar(); // eat the newline
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * run_intro()
 * ------------
 * function   : sets up the game environment
 *            :
 * parameters : two pointers to ints that will hold the size of
 *            : the board and the number of players
 *            :
 * returns    : nothing
 */
void run_intro(int *s, int *n)
{
    char buff, help[6];

    printf( "----------------\n" );
    printf( "Tic - Tac - Toe!\n" );
    printf( "----------------\n\n" );

    printf( "If you would like instructions, enter \"help\"; otherwise, "
            "just press Enter key: " );

    fgets(help, 5, stdin);

    if ( !strcmp(help, "help") )
        show_help();

    puts( "\nFirst we need to set up the game; "
          "this will only take 2 steps.\n" );

    puts( "[Step 1]" );
    printf( "Would you like a regular 3x3 game (Y or N)? [default: Y] " );

    buff = getchar();

    if ( (buff == 'y') || (buff == 'Y') || (buff == '\n') )
        *s = 3; // user wants standard game, so 3x3 matrix
    else
    {
        puts( "\nOk, let's set the size of the board...\n" );

        printf( "Enter the number of rows in the matrix: " );
        scanf( "%d", s );
    }

    puts( "\n\n[Step 2]" );
    printf( "How many players, 1 or 2? " );
    scanf( "%d", n );
        
    return;
}
