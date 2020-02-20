#include <stdlib.h>

#include "base.h"


Keyboard* Keyboard_init() {
    Keyboard* ret = malloc(sizeof(Keyboard));

    ret->key_left_pressed = false;
    ret->key_right_pressed = false;
    ret->key_up_pressed = false;
    ret->key_down_pressed = false;

    return ret;
}
