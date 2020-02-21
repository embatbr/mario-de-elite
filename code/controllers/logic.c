#include <stdbool.h>

#include <allegro5/allegro_primitives.h>

#include "logic.h"


void capture_keyboard_event(ALLEGRO_EVENT ev, Keyboard* keyboard) {
    bool key_is_down = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
    bool key_is_up = (ev.type == ALLEGRO_EVENT_KEY_UP);

    if(key_is_down || key_is_up) {
        int keycode = ev.keyboard.keycode;

        if(keycode == KEY_PAUSE) {
            keyboard->key_pause_pressed = key_is_down;
        }
        if(keycode == KEY_LEFT) {
            keyboard->key_left_pressed = key_is_down;
        }
        if(keycode == KEY_RIGHT) {
            keyboard->key_right_pressed = key_is_down;
        }
        if(keycode == KEY_UP) {
            keyboard->key_up_pressed = key_is_down;
        }
        if(keycode == KEY_DOWN) {
            keyboard->key_down_pressed = key_is_down;
        }
    }
}

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


void capture_mouse_event(ALLEGRO_EVENT ev, Mouse* mouse) {
    if(ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
        mouse->inside_display = true;
    }
    if(ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) {
        mouse->inside_display = false;
    }

    if(mouse->inside_display) {
        bool button_is_down = (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN);
        bool button_is_up = (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP);
        if(button_is_down || button_is_up) {
            int button = ev.mouse.button;

            if(button == BUTTON_LEFT) {
                bool prev_value = mouse->button_left_pressed;
                mouse->button_left_pressed = button_is_down ? true : (button_is_up ? false : prev_value);
            }
            if(button == BUTTON_RIGHT) {
                bool prev_value = mouse->button_right_pressed;
                mouse->button_right_pressed = button_is_down ? true : (button_is_up ? false : prev_value);
            }
            if(button == BUTTON_MIDDLE) {
                bool prev_value = mouse->button_middle_pressed;
                mouse->button_middle_pressed = button_is_down ? true : (button_is_up ? false : prev_value);
            }
        }

        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouse->position->x_axis = ev.mouse.x;
            mouse->position->y_axis = ev.mouse.y;
        }
    }
}
