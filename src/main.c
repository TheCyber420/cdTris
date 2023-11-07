/**
 * @brief   The main method of the program, calls the necesarry functions to
 *          start running the game
 * 
 * @return  * int 
 */
#include "gamecontroller.h"
int main() {
    SetRandomSeed(52);
    SetTargetFPS(120);
    init_controls();
    init_game();
    start_game();
    return 0;
}