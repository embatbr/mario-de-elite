#pragma once

#include "Point2D.h"


class Box2D {
    public:
        Point2D* position;
        int width;
        int height;

        Box2D(int x_pos, int y_pos, int width, int height);
        ~Box2D();

        void move(int x_delta, int y_delta);
};
