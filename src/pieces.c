/**
 * @file          pieces.c
 * @author        Christiaan Cornelissen
 * 
 * @brief         code for handeling piece movement and rotation
 */
#include "pieces.h"
#include <stdio.h>
typedef unsigned char BYTE;


/* =====================================================================
 *   Global Variables
 * =====================================================================
 */
// BYTE piece_bag[] = {1, 2, 3, 4, 5, 6, 7};
BYTE piece_bag[] = {4, 4, 4, 4, 4, 4, 4};
BYTE piece_number = 7;
//The tetris game makes use of offset tables when rotating in order to be able to "kick" pieces (nudging them when rotating)
//this is useful when rotating next to a wall or when you want to preform things like T-spins
//Each row represents a rotation and each column represents an offset which will be added to the position
//The offset is found by taking the      starting rotation offset (in row n) - end rotation offset (in row n)
//That offset is then added to the position and if the piece is in a legal spot then, then it is rotated
//each pair off ofsets is tried from n = 1 to n = 5
int offset_table_a[] = {  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,
                           0, 0,  1, 0, 1, -1,  0, 2,  1, 2,
                           0, 0,  0, 0,  0, 0,  0, 0,  0, 0,
                           0, 0, -1, 0,-1, -1,  0, 2, -1, 2 };

int offset_table_b[] = {  0, 0, -1, 0,  2, 0, -1, 0,  2, 0,
                          -1, 0,  0, 0,  0, 0,  0, 1,  0, 2,
                          -1, 1,  1, 1, -2, 1,  1, 0, -2, 0,
                           0, 1,  0, 1,  0, 1, 0, -1,  0, 2 };


bool legal_position(Piece p, int board[]);

/* =====================================================================
 *   Public functions
 * =====================================================================
 */

/**
 * @brief         Checks if a piece can move in a certain direction
 * 
 * @param p       the piece data of the falling piece
 * @param board   the board of tiles that the piece can collide with
 * @param dir     the direction that the piece is trying to move in
 * 
 * @return true   if the piece can move and shifts the coordinates;
 * @return false  the piece cannot move in that direction
 */
bool move_piece(Piece *p, int board[], Vector2 dir)
{   
    Piece q = *p;

    q.position.x += dir.x;
    q.position.y += dir.y;

    if (legal_position(q, board)) {
        *p = q;
        return true;
    } else {
        return false;
    } 
}

/**
 * @brief         checks if a piece can rotate in a certain direction 
 *                and rotates it if possible
 * @param p       the piece to be rotated
 * @param board   the board of tiles the piece can collide with 
 * @param num_rotations 
 *                the number of times the piece has to rotate since all rotations are
 *                always clockwise
 */
void rotate_piece(Piece *p, int board[], BYTE num_rotations)
{  
    if (p->piece_id == 4) {
        return;
    }
    Piece q = *p, d;
    int x, y, old_rot, new_rot;
    old_rot = q.rotation;
    new_rot = (old_rot + num_rotations) % 4;
    for (int i = 0; i < num_rotations; i++) {
        for (int k = 0; k < 4; k++) {
            x = q.tiles[k].x;
            y = q.tiles[k].y;

            q.tiles[k].x = y;
            q.tiles[k].y = -x;           
        }
    }
    for (int a = 0; a < 5; a++) {
        d = q;
        if (d.piece_id != 1) {
            d.position.x += (offset_table_a[old_rot * 10 + a * 2] - offset_table_a[new_rot * 10 + a * 2]);
            d.position.y += (offset_table_a[old_rot * 10 + a * 2 + 1] - offset_table_a[new_rot * 10 + a * 2 + 1]);
        } else {
            d.position.x += (offset_table_b[old_rot * 10 + a * 2] - offset_table_b[new_rot * 10 + a * 2]);
            d.position.y += (offset_table_b[old_rot * 10 + a * 2 + 1] - offset_table_b[new_rot * 10 + a * 2 + 1]);
        }
        if (legal_position(d, board)) {
            d.rotation = new_rot;
            *p = d;
            return;
        }
    }
}
/**
 * @brief         checks if the bag has pieces left, otherwise a new bag is generated
 * 
 * @return BYTE   the next piece in the bag/first piece in new bag
 */
BYTE next_piece(void)
{
    return (piece_number < 7) ? piece_bag[piece_number++] : shuffle_bag();
}

/**
 * @brief         generates a new piece bag
 * 
 * @return BYTE   returns the first piece of the new bag
 */
BYTE shuffle_bag(void)
{   
    unsigned int r, temp;
    unsigned int i;
    //Fisher-Yates shuffle to randomise array
    for (i = 6; i > 0; i--) {
        r = GetRandomValue(0, i);

        temp = piece_bag[i];
        piece_bag[i] = piece_bag[r];
        piece_bag[r] = temp;
    }

    piece_number = 0;
    return piece_bag[piece_number++];
}
/**
 * @brief         populates the piece object with values corresponding to
 *                the piece id
 * 
 * @param p       the piece oject
 * @param id      piece id
 */
void get_piece(Piece* p, BYTE id)
{
    p->piece_id = id;
    p->rotation = 0;
    p->position = (Vector2) {4, 20};
    p->tiles[0] = (Vector2) {0, 0};
    switch (id) {
        case 1: //line piece
            p->tiles[1] = (Vector2) {-1, 0};
            p->tiles[2] = (Vector2) {1, 0};
            p->tiles[3] = (Vector2) {2, 0};
            break;
        case 2: //j-piece
            p->tiles[1] = (Vector2) {-1, 0};
            p->tiles[2] = (Vector2) {-1, 1};
            p->tiles[3] = (Vector2) {1, 0};
            break;
        case 3: //L-piece
            p->tiles[1] = (Vector2) {-1, 0};
            p->tiles[2] = (Vector2) {1, 0};
            p->tiles[3] = (Vector2) {1, 1};
            break;
        case 4: //O-piece
            p->tiles[1] = (Vector2) {1, 0};
            p->tiles[2] = (Vector2) {1, 1};
            p->tiles[3] = (Vector2) {0, 1};
            break;
        case 5: //S-piece
            p->tiles[1] = (Vector2) {0, 1};
            p->tiles[2] = (Vector2) {1, 1};
            p->tiles[3] = (Vector2) {-1, 0};
            break;
        case 6: //Z-piece
            p->tiles[1] = (Vector2) {0, 1};
            p->tiles[2] = (Vector2) {-1, 1};
            p->tiles[3] = (Vector2) {1, 0};
            break;
        case 7: //T-piece
            p->tiles[1] = (Vector2) {0, 1};
            p->tiles[2] = (Vector2) {1, 0};
            p->tiles[3] = (Vector2) {-1, 0};
            break;
        default:
            break;
    }
}

/* =====================================================================
 *   Private functions
 * =====================================================================
 */

/**
 * @brief         Checks if the given piece doesn't collide with other stationary tiles or 
 *                or is out of bounds
 * 
 * @param p       The piece being checked
 * @param board   The board which the piece is being compared to
 * @return true   if the piece is in a legal spot
 * @return false  if it isn't
 */
bool legal_position(Piece p, int board[])
{   
    int x, y;

    for (int i = 0; i < 4; i++) {
        x = p.position.x + p.tiles[i].x;
        y = p.position.y + p.tiles[i].y;

        if (y < 0 || x > 9 || x < 0) {   //checks whether piece is off the sides or under the map
            return false;
        }
        if (board[y * 10 + x] != 0) {      //checks whether the each tile is on an empty board space
            return false;
        }
    }
    return true;   
}
