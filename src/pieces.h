/**
 * @file    pieces.h
 * @author  your name (you@domain.com)
 * 
 * @brief   Api for piece-relation functions
 *          like rotating and moving the falling piece
 */
#include <raylib.h>
typedef unsigned char BYTE;

typedef struct Piece {
    BYTE piece_id;
    Vector2 tiles[4];
    Vector2 position;
    BYTE rotation;
} Piece;


bool move_piece(Piece *p, int board[], Vector2 dir);
void rotate_piece(Piece *p, int board[], BYTE num_rotations);
void get_piece(Piece* p, BYTE id);
BYTE next_piece(void);
BYTE shuffle_bag(void);