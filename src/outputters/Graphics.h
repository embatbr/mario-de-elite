#pragma once

#include <list>
#include <tuple>
using namespace std;

#include "../base/Object2D.h"
#include "../base/Point2D.h"


class Graphics {
    public:
        Graphics();
        ~Graphics();

        void draw_contour(list<tuple<Point2D, Point2D, Object2DType>> cur_state);
};
