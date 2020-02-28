#pragma once

#include <string>
using namespace std;

#include "../base/Object2D.h"


class Phase {
    protected:
        int player_x_pos;
        int player_y_pos;
        int player_width;
        int player_height;

    public:
        Phase() {}
        ~Phase() {}

        Object2D* load_player() {
            return new Object2D(
                this->player_x_pos,
                this->player_y_pos,
                this->player_width,
                this->player_height
            );
        }
};


class Phase1: public Phase {
    public:

        Phase1(): Phase() {
            this->player_x_pos = 100;
            this->player_y_pos = 400;
            this->player_width = 20;
            this->player_height = 35;
        }
        ~Phase1() {}
};


Phase load_phase(string name) {
    if(name.compare("1") == 0) {
        return Phase1();
    }

    return Phase();
}
