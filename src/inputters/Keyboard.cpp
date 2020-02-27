#include "Keyboard.h"
#include "../settings/InputKeys.h"
#include "../settings/Inputs.h"


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

        if(keycode == InputKeys::PAUSE) {
            this->key_pause_pressed = key_is_down;
        }
        if(keycode == InputKeys::LEFT) {
            this->key_left_pressed = key_is_down;
        }
        if(keycode == InputKeys::RIGHT) {
            this->key_right_pressed = key_is_down;
        }
        if(keycode == InputKeys::UP) {
            this->key_up_pressed = key_is_down;
        }
        if(keycode == InputKeys::DOWN) {
            this->key_down_pressed = key_is_down;
        }
    }
}

map<string, bool> Keyboard::read() {
    map<string, bool> keys;

    keys[INPUT_KEY_PAUSE] = this->key_pause_pressed;
    keys[INPUT_KEY_LEFT] = this->key_left_pressed;
    keys[INPUT_KEY_RIGHT] = this->key_right_pressed;
    keys[INPUT_KEY_UP] = this->key_up_pressed;
    keys[INPUT_KEY_DOWN] = this->key_down_pressed;

    return keys;
}
