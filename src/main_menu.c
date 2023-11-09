#include "main_menu.h"

void start_main_menu(void)
{
    Button start_game_button = {0, 0, 100, 500};
    bool in_menu = true;

    init_window();

    //draw button
    while (in_menu && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_button(start_game_button);
        EndDrawing();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && in_button_range(start_game_button)) {
            init_controls();
            init_game();
            start_game();
            //in_menu = false;
        }
    }
}

bool in_button_range(Button b)
{
    int x = GetMouseX(), y = GetMouseY();
    return (range(x, b.x, b.x + b.width) && range(y, b.y, b.height)) ? true : false;
}

bool range(int n, int low, int high)
{
    return (n >= low && n <= high) ? true : false;
}

void draw_button(Button b)
{
    DrawRectangle(b.x, b.y, b.width, b.height, (Color) {255, 255, 255, 255});
}
