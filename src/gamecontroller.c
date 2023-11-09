/**
 * @file    game_controller.c
 * @author  Christiaan Cornelissen
 * 
 * @brief   Responsible for starting the game and hosting the ruleset
 */

#include "gamecontroller.h"

#define BOARD_HEIGHT 22
#define BOARD_WIDTH  10
int board[BOARD_HEIGHT * BOARD_WIDTH];

/* =====================================================================
 *   Global Variables
 * =====================================================================
 */

int das_timer, das_delay, score;
double clock, update_time;
bool can_hold = true;
Piece active_piece, piece_next, held_piece;
Controls input;

/**
 * @name    new_game
 * @brief   sets up for a new game
 */
void init_game(void)
{
    //empty all the board squares
    for (int i = 0; i < 220; i++) {
        board[i] = 0;
    }
    clock = 0;
    score = 0;
    update_time = 1000;                                            //number of miliseconds before the gamestate updates 
    held_piece.piece_id = 0;
    init_bag();
    get_piece(&active_piece, next_piece());
    get_piece(&piece_next, next_piece());
}
/**
 * @brief   Starts the game once everything has been set up
 *          Hosts the gameloop which progresses the game
 * 
 */
void start_game(void)
{
    bool running = 1;
    while (running) {                             //gameloop
        draw_board(board, active_piece, piece_next, held_piece, score);
        user_input();
        clock += GetFrameTime() * 1000;
        if (clock >= update_time) {
            clock = 0;
            if (move_piece(&active_piece, board, (Vector2) {0, -1}) == false) {   //if piece cannot go down, add it to the non-active pieces
                if (!add_piece_to_board()) {                                        //and spawn a new one
                    running = false;
                    continue;
                }         
                remove_rows();
                can_hold = true;
                update_time *= 0.99;
            }
        }
    }
}
/**
 * @brief  Assigns a default key to each game-action
 * 
 */
void init_controls(void)
{
    input.LEFT = KEY_A;
    input.RIGHT = KEY_D;
    input.HARD_DROP = KEY_SPACE;
    input.SOFT_DROP = KEY_S;
    input.ROTATE1 = KEY_W;
    input.ROTATE2 = KEY_Q;
    input.ROTATE3 = KEY_E;
    input.HOLD = KEY_C;
    input.DAS = 133;
    input.DAS_DELAY = 10;
}

/**
 * @brief       adds the active piece to the board of pieces and sets
 *              the next piece as the new active piece
 */
bool add_piece_to_board(void)
{
    int x, y;
    
    for (int i = 0; i < 4; i++) {
        x = active_piece.position.x + active_piece.tiles[i].x;
        y = active_piece.position.y + active_piece.tiles[i].y;

        board[y * 10 + x] = (BYTE)active_piece.piece_id;
    }
    if (y >= 20) {
        return false;
    }
    active_piece = piece_next;
    get_piece(&piece_next, next_piece());
    return true;
}

/**
 * @brief       Checks for all possible user input and handles everyting related to
 *              the actions being taken by the player
 * 
 */
void user_input(void)
{
    if (IsKeyPressed(input.LEFT)) {
        move_piece(&active_piece, board, (Vector2){-1, 0});
        das_timer = 0;
        das_delay = 0;
    } else if (IsKeyDown(input.LEFT)) {
        das_timer += GetFrameTime() * 1000;
        das_delay -= GetFrameTime() * 1000;
        if (das_timer >= input.DAS && das_delay <= 0) {
            move_piece(&active_piece, board, (Vector2){-1, 0});
            das_delay = input.DAS_DELAY;
        }
    }
    if (IsKeyPressed(input.RIGHT)) {
        move_piece(&active_piece, board, (Vector2){1, 0});
        das_timer = 0;
        das_delay = 0;
    } else if (IsKeyDown(input.RIGHT)) {
        das_timer += GetFrameTime() * 1000;
        das_delay -= GetFrameTime() * 1000;
        if (das_timer >= input.DAS && das_delay <= 0) { 
            move_piece(&active_piece, board, (Vector2){1, 0});
            das_delay = input.DAS_DELAY;
        }
    }
    if (IsKeyPressed(input.HARD_DROP)) {
        while (move_piece(&active_piece, board, (Vector2) {0, -1}) != false);
        clock = update_time;
    }
    if (IsKeyPressed(input.ROTATE1)) {
        rotate_piece(&active_piece, board, 1);
    }
    if (IsKeyPressed(input.ROTATE2)) {
        rotate_piece(&active_piece, board, 2);
    }
    if (IsKeyPressed(input.ROTATE3)) {
        rotate_piece(&active_piece, board, 3);
    }
    if (IsKeyDown(input.SOFT_DROP)) {
        move_piece(&active_piece, board, (Vector2){0, -1});
    }
    if (IsKeyPressed(input.HOLD)) {
        Piece temp;
        if (can_hold && held_piece.piece_id == 0) {
            get_piece(&held_piece, active_piece.piece_id);
            active_piece = piece_next;
            get_piece(&piece_next, next_piece());
            can_hold = false;
        } else if (can_hold) {
            can_hold = false;
            temp = held_piece;
            get_piece(&held_piece, active_piece.piece_id);
            active_piece = temp;
        }
    }
}

/**
 * @brief      Checks if there are any full rows and deletes them and moves all the other rows down
 *             by 1
 *             if 4 rows are removed at once, it is a Tetris
 */
void remove_rows(void)
{
    int counter = 0, row_counter = 0;
    for (int y = 0; y < 20; y++) {
        counter = 0;
        for (int x = 0; x < 10; x++) {
            if (board[y * 10 + x] != 0) 
                counter++;
        }
        if (counter == 10) {
            row_counter++;
            for (int a = y; a < 19; a++) {
                for (int x = 0; x < 10; x++) {
                    board[a * 10 + x] = board[(a + 1) * 10 + x];
                }
            }
            y--;
        }
    }
    score += row_counter * 100;
    if (row_counter == 4) {
        score += 400;
    }
}