#pragma once

#include <tuple>
using namespace std;

#include "Box2D.h"
#include "Point2D.h"


class Object2D {
    private:
        Point2D* position;
        Box2D* box;

    public:
        int x_speed;
        int y_speed;

        Object2D(int x_pos, int y_pos, int width, int height);
        ~Object2D();

        void move();
        tuple<Point2D, Point2D> get_drawing_points();
};
