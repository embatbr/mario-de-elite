#include "Point2D.h"


Point2D::Point2D(int x_axis, int y_axis) {
    this->x_axis = x_axis;
    this->y_axis = y_axis;
}


Point2D::~Point2D() {}


void Point2D::move(int x_delta, int y_delta) {
    this->x_axis = this->x_axis + x_delta;
    this->y_axis = this->y_axis + y_delta;
}
