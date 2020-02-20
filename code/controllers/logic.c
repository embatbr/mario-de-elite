#include "logic.h"


int direction_by_key(bool negative_key, bool positive_key) {
    if(negative_key && !positive_key) {
        return -1;
    }
    if(!negative_key && positive_key) {
        return 1;
    }

    return 0;
}

int direction_h(Keyboard* keyboard) {
    return direction_by_key(keyboard->key_left_pressed, keyboard->key_right_pressed);
}

int direction_v(Keyboard* keyboard) {
    return direction_by_key(keyboard->key_up_pressed, keyboard->key_down_pressed);
}
