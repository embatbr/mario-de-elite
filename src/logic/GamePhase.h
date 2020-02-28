#pragma once

#include <list>
#include <map>
#include <string>
#include <tuple>
using namespace std;

#include "../base/Object2D.h"


class GamePhase {
    private:
        string name;
        Object2D *player;
        list<Object2D*> enemies;

        tuple<int, int> process_key_input(map<string, bool> keys);

    public:
        GamePhase(string name);
        ~GamePhase();

        list<tuple<Point2D, Point2D, Object2DType>> update(map<string, bool> keys);
};
