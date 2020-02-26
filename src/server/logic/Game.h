#pragma once

#include <iostream>
#include <list>
#include <string>
using namespace std;

#include "../base/Point2D.h"


class Game {
    private:
        Point2D *player;
        int width;
        int height;
        int x_speed;
        int y_speed;

    public:
        Game();
        ~Game();

        list<string> run(string input);
};
