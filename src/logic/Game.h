#pragma once

#include <map>
#include <string>
#include <tuple>
using namespace std;

#include "../base/Box2D.h"


class Game {
    private:
        Box2D *player;

        tuple<int, int> process_key_input(map<string, bool> keys);

    public:
        Game();
        ~Game();

        tuple<Point2D, Point2D> update(map<string, bool> keys);
};
