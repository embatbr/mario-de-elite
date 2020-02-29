#pragma once

#include <tuple>
using namespace std;

#include "Box2D.h"
#include "Point2D.h"


typedef enum {
    OBJECT_PLATFORM,
    OBJECT_BLOCK,
    OBJECT_ENEMY,
    OBJECT_PLAYER,
    OBJECT_BULLET
} Object2DType;

class Object2D {
    private:
        Point2D* position;
        Box2D* box;
        Object2DType type;

    public:
        int x_speed;
        int y_speed;

        Object2D(int x_pos, int y_pos, int width, int height, Object2DType type);
        ~Object2D();

        Object2DType get_type();

        void move();
        tuple<Point2D, Point2D, Object2DType> get_drawing_contour();
};
