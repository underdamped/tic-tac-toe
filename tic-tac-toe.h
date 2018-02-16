/* tic-tac-toe.h -- header file
 *
 * Javier Lombillo <javier@asymptotic.org>
 * 2013-04-25
 */

#ifndef TICTACTOE_HEADER
#define TICTACTOE_HEADER

#include <stdio.h>

#define VERSION 0.1

/* this structure will represent the game board, the essence
 * of which is a matrix with run-time determined size; the "moves"
 * var will keep a running count of total moves made, which is
 * an easy way to determine a draw state
 */
struct game_board
{
    int size;
    int moves;
    int **board;
};

/* this struct represents a player. each player will have a
 * name, a mark character ('X' or 'O'), a number associated
 * with a winnning board state (see NOTE in check_winner()
 * comments for details), and finally a human- or computer-
 * appropriate move function. by using a pointer to a function
 * we can assign the proper move function at run-time, depending
 * on whether the user chooses 1- or 2-player game.
 */
struct player_object
{
    char name[50];
    char mark;
    int  win;
    int (*move_func)(struct game_board *, struct player_object *);
};

#endif
