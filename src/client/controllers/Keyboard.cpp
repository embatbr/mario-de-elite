#include "Keyboard.h"


Keyboard::Keyboard() {
    this->key_pause_pressed = false;
    this->key_left_pressed = false;
    this->key_right_pressed = false;
    this->key_up_pressed = false;
    this->key_down_pressed = false;
}


Keyboard::~Keyboard() {}


void Keyboard::capture(ALLEGRO_EVENT ev) {
    bool key_is_down = ev.type == ALLEGRO_EVENT_KEY_DOWN;
    bool key_is_up = ev.type == ALLEGRO_EVENT_KEY_UP;

    if(key_is_down || key_is_up) {
        int keycode = ev.keyboard.keycode;

        if(keycode == KEY_PAUSE) {
            this->key_pause_pressed = key_is_down;
        }
        if(keycode == KEY_LEFT) {
            this->key_left_pressed = key_is_down;
        }
        if(keycode == KEY_RIGHT) {
            this->key_right_pressed = key_is_down;
        }
        if(keycode == KEY_UP) {
            this->key_up_pressed = key_is_down;
        }
        if(keycode == KEY_DOWN) {
            this->key_down_pressed = key_is_down;
        }
    }
}

map<int, bool> Keyboard::read() {
    map<int, bool> keys;

    keys[KEY_PAUSE] = this->key_pause_pressed;
    keys[KEY_LEFT] = this->key_left_pressed;
    keys[KEY_RIGHT] = this->key_right_pressed;
    keys[KEY_UP] = this->key_up_pressed;
    keys[KEY_DOWN] = this->key_down_pressed;

    return keys;
}
