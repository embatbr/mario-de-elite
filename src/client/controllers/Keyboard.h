#pragma once

#include <map>
using namespace std;

#include <allegro5/allegro.h>


#define KEY_PAUSE 59 // ESC
#define KEY_SELECT 67 // ENTER
#define KEY_LEFT 1 // A
#define KEY_RIGHT 4 // D
#define KEY_UP 23 // W
#define KEY_DOWN 19 // S


class Keyboard {
    private:
        bool key_pause_pressed;
        bool key_select_pressed;

        bool key_left_pressed;
        bool key_right_pressed;
        bool key_up_pressed;
        bool key_down_pressed;

    public:
        Keyboard();
        ~Keyboard();

        void capture(ALLEGRO_EVENT ev);
        map<int, bool> read();
};
