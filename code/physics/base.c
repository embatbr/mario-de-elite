#include <stdlib.h>

#include "base.h"


Point2D* Point2D_init(int x_axis, int y_axis) {
    Point2D* ret = malloc(sizeof(Point2D));

    ret->x_axis = x_axis;
    ret->y_axis = y_axis;

    return ret;
}

void Point2D_del(Point2D* param) {
    free(param);
}


Box2D* Box2D_init(int width, int height) {
    Box2D* ret = malloc(sizeof(Box2D));

    ret->width = width;
    ret->height = height;

    return ret;
}

void Box2D_del(Box2D* param) {
    free(param);
}


Speed2D* Speed2D_init(int x_axis, int y_axis) {
    Speed2D* ret = malloc(sizeof(Speed2D));

    ret->x_axis = x_axis;
    ret->y_axis = y_axis;

    return ret;
}

void Speed2D_del(Speed2D* param) {
    free(param);
}


Object2D* Object2D_init(Point2D* position, Box2D* box, Speed2D* speed, bool has_gravity) {
    Object2D* ret = malloc(sizeof(Object2D));

    ret->position = position;
    ret->box = box;
    ret->speed = speed;
    ret->has_gravity = has_gravity;

    return ret;
}

Object2D* Object2D_init_2(int x_pos, int y_pos, int width, int height, int x_speed,
                          int y_speed, bool has_gravity) {
    Point2D* position = Point2D_init(x_pos, y_pos);
    Box2D* box = Box2D_init(width, height);
    Speed2D* speed = Speed2D_init(x_speed, y_speed);

    return Object2D_init(position, box, speed, has_gravity);
}

void Object2D_del(Object2D* param) {
    free(param->position);
    free(param->box);
    free(param->speed);
    free(param);
}
