#pragma once

#include <map>
#include <string>
using namespace std;

#include <allegro5/allegro.h>


class Keyboard {
    private:
        bool key_pause_pressed;
        bool key_left_pressed;
        bool key_right_pressed;
        bool key_up_pressed;
        bool key_down_pressed;

    public:
        Keyboard();
        ~Keyboard();

        void capture(ALLEGRO_EVENT ev);
        map<string, bool> read();
};
