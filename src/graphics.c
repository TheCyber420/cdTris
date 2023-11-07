/**
 * @file    graphics.c
 * @author  Christiaan Cornelissen
 * 
 * @brief   all functions used to handle the display and the window
 * 
 */
#include "graphics.h"
#include <stdio.h>
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 880
#define TILE_WIDTH 40
/**
 * @name   init_window
 * @brief  creates a new window to house visuals
 */
void init_window(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
}
/**
 * @name   draw_pieces
 * @brief  draws all the non-moving tiles onto the window
 * 
 * @param board 
 *         the board containing all the tiles to be drawn        
 */
void draw_pieces(int board[]) {
    for (int y = 0; y < 22; y++) {
        for (int x = 0; x < 10; x++) {
            if (board[y * 10 + x] != 0) {
                DrawRectangle(x * TILE_WIDTH, WINDOW_HEIGHT - (y + 1) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, get_color(board[y * 10 + x], 255));
            }
        }
    }
}

void draw_active_piece(Piece p, int board[])
{   
    Piece gp = p;
    while (move_piece(&gp, board, (Vector2) {0, -1}) != false);
    int x, y, gx, gy;

    for (int i = 0; i < 4; i++) {
        x = p.position.x + p.tiles[i].x;
        y = p.position.y + p.tiles[i].y;

        gx = gp.position.x + gp.tiles[i].x;
        gy = gp.position.y + gp.tiles[i].y;

        DrawRectangle(gx * TILE_WIDTH, WINDOW_HEIGHT - (gy + 1) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, get_color(gp.piece_id, 100));
        DrawRectangle(x * TILE_WIDTH, WINDOW_HEIGHT - (y + 1) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, get_color(p.piece_id, 255));
    }
}
/**
 * @brief   Assigns a custom color to a piece based off of what piece it is
 * 
 * @param id
 *          The piece id number 
 * @return Color 
 *          The custom color
 */
Color get_color(BYTE id, int alpha)
{
    switch (id) {
        case 1: return (Color) {51, 255, 255, alpha};
            break;
        case 2: return (Color) {0, 0, 210, alpha};
            break;
        case 3: return (Color) {255, 153, 51, alpha};
            break;
        case 4: return (Color) {255, 255, 0, alpha};
            break;
        case 5: return (Color) {0, 255, 0, alpha};
            break;
        case 6: return (Color) {153, 0, 153, alpha};
            break;
        case 7: return (Color) {255, 0, 0, alpha};
            break;
        default: return (Color) {0, 0, 0, 0};
            break;
    }
}

void draw_board(int board[], Piece active_piece) 
{
        ClearBackground(DARKGRAY);
        BeginDrawing();
        draw_active_piece(active_piece, board);
        draw_pieces(board);
        EndDrawing();
}
