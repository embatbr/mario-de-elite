#include <stdlib.h>

#include "base.h"


Point2D* Point2D_init(int x_axis, int y_axis) {
    Point2D* ret = malloc(sizeof(Point2D));

    ret->x_axis = x_axis;
    ret->y_axis = y_axis;

    return ret;
}


Box2D* Box2D_init(int width, int height) {
    Box2D* ret = malloc(sizeof(Box2D));

    ret->width = width;
    ret->height = height;

    return ret;
}


Speed2D* Speed2D_init(int x_axis, int y_axis) {
    Speed2D* ret = malloc(sizeof(Speed2D));

    ret->x_axis = x_axis;
    ret->y_axis = y_axis;

    return ret;
}


Object2D* Object2D_init(Point2D* position, Box2D* collision_box, Speed2D* speed,
                        bool has_gravity) {
    Object2D* ret = malloc(sizeof(Object2D));

    ret->position = position;
    ret->collision_box = collision_box;
    ret->speed = speed;
    ret->has_gravity = has_gravity;

    return ret;
}

Object2D* Object2D_init_2(int x_pos, int y_pos, int width, int height, int x_speed,
                          int y_speed, bool has_gravity) {
    Point2D* position = malloc(sizeof(Point2D));
    position->x_axis = x_pos;
    position->y_axis = y_pos;

    Box2D* collision_box = malloc(sizeof(Box2D));
    collision_box->width = width;
    collision_box->height = height;

    Speed2D* speed = malloc(sizeof(Speed2D));
    speed->x_axis = x_speed;
    speed->y_axis = y_speed;

    return Object2D_init(position, collision_box, speed, has_gravity);
}
