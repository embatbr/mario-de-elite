#pragma once

#include <tuple>
using namespace std;

#include "../base/Point2D.h"


class Graphics {
    public:
        Graphics();
        ~Graphics();

        void paint_contour(tuple<Point2D, Point2D> points);
};
