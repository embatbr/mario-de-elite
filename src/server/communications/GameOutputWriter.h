#pragma once


#include <list>
#include <string>
using namespace std;

#include "../base/Point2D.h"


class GameOutputWriter {
    public:
        GameOutputWriter();
        ~GameOutputWriter();

        // void write(Point2D* player);
        list<string> write(Point2D* player, int width, int height);
};
