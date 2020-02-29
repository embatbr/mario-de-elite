#include "Object2D.h"


Object2D::Object2D(int x_pos, int y_pos, int width, int height, Object2DType type) {
    if(type == OBJECT_PLATFORM) {
        height = 0;
    }
    // else if(width <= 0 || height <= 0) {
    //     throw "width and height must be positive integers";
    // }

    this->position = new Point2D(x_pos, y_pos);
    this->box = new Box2D(width, height);
    this->type = type;

    this->x_speed = 0;
    this->y_speed = 0;
}


Object2D::~Object2D() {}


Object2DType Object2D::get_type() {
    return this->type;
}


void Object2D::move() {
    this->position->move(this->x_speed, this->y_speed);
}


tuple<Point2D, Point2D, Object2DType> Object2D::get_drawing_contour() {
    Point2D sup_left = Point2D(
        this->position->x_axis - this->box->width/2,
        this->position->y_axis - this->box->height/2
    );

    Point2D inf_right = Point2D(
        this->position->x_axis + this->box->width/2,
        this->position->y_axis + this->box->height/2
    );

    return tuple<Point2D, Point2D, Object2DType>{sup_left, inf_right, this->type};
}
