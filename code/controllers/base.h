#pragma once

/**
Base functions and types for game controlling (keyboard and mouse).
*/

#include <stdbool.h>


#define KEY_EXIT 59 // ESC
#define KEY_PAUSE 67 // ENTER

#define KEY_LEFT 1 // A
#define KEY_RIGHT 4 // D
#define KEY_UP 23 // W
#define KEY_DOWN 19 // S


typedef struct {
    bool key_exit_pressed;
    bool key_pause_pressed;
    bool key_left_pressed;
    bool key_right_pressed;
    bool key_up_pressed;
    bool key_down_pressed;
} Keyboard;

Keyboard* Keyboard_init();


// typedef struct {
// } Mouse;


// typedef struct {
//     Keyboard* keyboard;
//     Mouse* mouse;
// } Controllers;
