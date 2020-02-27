#include "Box2D.h"


Box2D::Box2D(int x_pos, int y_pos, int width, int height) {
    this->position = new Point2D(x_pos, y_pos);
    this->width = width;
    this->height = height;
}


Box2D::~Box2D() {
    delete this->position;
}


void Box2D::move(int x_delta, int y_delta) {
    this->position->move(x_delta, y_delta);
}
