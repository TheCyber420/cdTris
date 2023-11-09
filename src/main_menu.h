#include "gamecontroller.h"

typedef struct buttons {
    unsigned short x;
    unsigned short y;
    unsigned short width;
    unsigned short height;
} Button;

void start_main_menu(void);
bool in_button_range(Button b);
bool range(int n, int low, int high);