#pragma once

/**
Base functions and types for game controlling (keyboard and mouse).
*/

#include <stdbool.h>

#include "../physics/base.h"


#define KEY_PAUSE 59 // ESC
#define KEY_LEFT 1 // A
#define KEY_RIGHT 4 // D
#define KEY_UP 23 // W
#define KEY_DOWN 19 // S


typedef struct {
    bool key_pause_pressed;
    bool key_left_pressed;
    bool key_right_pressed;
    bool key_up_pressed;
    bool key_down_pressed;
} Keyboard;

Keyboard* Keyboard_init();


#define BUTTON_LEFT 1
#define BUTTON_RIGHT 2
#define BUTTON_MIDDLE 3 // the wheel when pressed

typedef struct {
    bool inside_display;
    Point2D* position;
    bool button_left_pressed;
    bool button_right_pressed;
    bool button_middle_pressed;
} Mouse;

Mouse* Mouse_init(int x_pos, int y_pos);


typedef struct {
    Keyboard* keyboard;
    Mouse* mouse;
} Controllers;

Controllers* Controllers_init(int mouse_x_pos, int mouse_y_pos);
