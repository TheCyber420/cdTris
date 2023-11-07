/**
 * @file    graphics.h    
 * @author  Christiaan Cornelissen
 * 
 * @brief   API for the graphics handeler
 *          Handles all the visual components and manages the window
 */
#include <raylib.h>
#include <unistd.h>
#include "pieces.h"

void draw_board(int board[], Piece active_piece);
void init_window(void);
void draw_visuals(void);
void draw_pieces(int board[]);
void draw_active_piece(Piece p, int board[]);
Color get_color(BYTE id, int alpha);