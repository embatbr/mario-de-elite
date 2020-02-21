#include <stdlib.h>

#include "base.h"


Keyboard* Keyboard_init() {
    Keyboard* ret = malloc(sizeof(Keyboard));

    ret->key_pause_pressed = false;
    ret->key_left_pressed = false;
    ret->key_right_pressed = false;
    ret->key_up_pressed = false;
    ret->key_down_pressed = false;

    return ret;
}


Mouse* Mouse_init() {
    Mouse* ret = malloc(sizeof(Mouse));

    ret->inside_display = false;
    ret->position = Point2D_init(0, 0);
    ret->button_left_pressed = false;
    ret->button_right_pressed = false;
    ret->button_middle_pressed = false;

    return ret;
}


Controllers* Controllers_init() {
    Controllers* ret = malloc(sizeof(Controllers));

    ret->keyboard = Keyboard_init();
    ret->mouse = Mouse_init();

    return ret;
}
