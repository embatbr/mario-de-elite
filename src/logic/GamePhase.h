#pragma once

#include <map>
#include <string>
#include <tuple>
using namespace std;

#include "../base/Object2D.h"


class GamePhase {
    private:
        string name;
        Object2D *player;

        tuple<int, int> process_key_input(map<string, bool> keys);

    public:
        GamePhase(string name);
        ~GamePhase();

        tuple<Point2D, Point2D> update(map<string, bool> keys);
};
