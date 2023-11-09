/**
 * @file    graphics.c
 * @author  Christiaan Cornelissen
 * 
 * @brief   all functions used to handle the display and the window
 * 
 */
#include "graphics.h"
#include <stdio.h>
#define WINDOW_WIDTH 800              //enough for 2 * 10 (5-10-5)
#define WINDOW_HEIGHT 880             //enough for 20 + 2 tiles
#define BOARD_HEIGHT 22
#define BOARD_WIDTH  10
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
    int x_offset = TILE_WIDTH * (BOARD_WIDTH >> 1);
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            DrawRectangle(x * TILE_WIDTH + x_offset, WINDOW_HEIGHT - (y + 1) * TILE_WIDTH, TILE_WIDTH * 0.95, TILE_WIDTH * 0.95, (Color) {20, 20, 20, 255});
            if (board[y * 10 + x] != 0) {
                DrawRectangle(x * TILE_WIDTH + x_offset, WINDOW_HEIGHT - (y + 1) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, get_color(board[y * 10 + x], 255));
            }
        }
    }
}

void draw_held_piece(Piece p)
{   
    int x, y;
    DrawText("Held Piece", TILE_WIDTH, TILE_WIDTH * 0.9, TILE_WIDTH >> 1, WHITE);
    DrawRectangle(TILE_WIDTH * 0.5, TILE_WIDTH * 1.5, TILE_WIDTH * 4, TILE_WIDTH * 3, (Color) {50, 50, 50, 255});
    for (int i = 0; i < 4; i++) {
        x = TILE_WIDTH * 2 + p.tiles[i].x * TILE_WIDTH;
        y = TILE_WIDTH * 3 - p.tiles[i].y * TILE_WIDTH;

        if (p.piece_id == 1 || p.piece_id == 4) {
            x -= TILE_WIDTH >> 1;
        }
        DrawRectangle(x, y, TILE_WIDTH, TILE_WIDTH, get_color(p.piece_id, 255));
    }
 }

void draw_active_piece(Piece p, int board[])
{   
    Piece gp = p;
    int x, y, gx, gy;
    int x_offset = TILE_WIDTH * (BOARD_WIDTH >> 1);

    while (move_piece(&gp, board, (Vector2) {0, -1}) != false);

    for (int i = 0; i < 4; i++) {
        x = p.position.x + p.tiles[i].x;
        y = p.position.y + p.tiles[i].y;

        gx = gp.position.x + gp.tiles[i].x;
        gy = gp.position.y + gp.tiles[i].y;

        DrawRectangle(gx * TILE_WIDTH + x_offset, WINDOW_HEIGHT - (gy + 1) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, get_color(gp.piece_id, 100));
        DrawRectangle(x * TILE_WIDTH + x_offset, WINDOW_HEIGHT - (y + 1) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, get_color(p.piece_id, 255));
    }
}
void draw_next_piece(Piece p)
{   
    int x, y;
    DrawText("Next Piece", TILE_WIDTH * 16, TILE_WIDTH * 0.9, TILE_WIDTH >> 1, WHITE);
    DrawRectangle(TILE_WIDTH * 15.5, TILE_WIDTH * 1.5, TILE_WIDTH * 4, TILE_WIDTH * 3, (Color) {50, 50, 50, 255});
    for (int i = 0; i < 4; i++) {
        x = TILE_WIDTH * 17 + p.tiles[i].x * TILE_WIDTH;
        y = TILE_WIDTH * 3 - p.tiles[i].y * TILE_WIDTH;

        if (p.piece_id == 1 || p.piece_id == 4) {
            x -= TILE_WIDTH >> 1;
        }
        DrawRectangle(x, y, TILE_WIDTH, TILE_WIDTH, get_color(p.piece_id, 255));
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
    // int rand = GetRandomValue(0, 255);
    // return (Color) {rand, rand, rand, GetRandomValue(0, 255)};
}

void draw_board(int board[], Piece active_piece, Piece piece_next, Piece held_piece) 
{
        ClearBackground((Color) {30, 30, 30});
        BeginDrawing();
        draw_held_piece(held_piece);
        draw_pieces(board);
        draw_next_piece(piece_next);
        draw_active_piece(active_piece, board);
        EndDrawing();
}
