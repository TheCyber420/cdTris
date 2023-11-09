/**
 * @file    gamecontroller.h
 * @author  Christiaan Cornelissen
 * 
 * @brief   Api for the game controller
 *          starts new games and implements the rules of tetris
 *          also handles all the live user input and screen updating
 */
#include <raylib.h>
#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>

typedef struct controller {
    int LEFT;
    int RIGHT;
    int HARD_DROP;
    int SOFT_DROP;
    int ROTATE1;
    int ROTATE2;
    int ROTATE3;
    int HOLD;

    int DAS;
    int DAS_DELAY;
} Controls;
void init_game(void); 
void init_controls(void);
void start_game(void);
void user_input(void);
bool add_piece_to_board(void);
void remove_rows(void);