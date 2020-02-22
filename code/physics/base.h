#pragma once

/**
Base types and functions to work with physics.
*/

#include <stdbool.h>


typedef struct {
    int x_axis;
    int y_axis;
} Point2D;

Point2D* Point2D_init(int x_axis, int y_axis);

void Point2D_del(Point2D* param);


typedef struct {
    int width;
    int height;
} Box2D;

Box2D* Box2D_init(int width, int height);

void Box2D_del(Box2D* param);


typedef struct {
    int x_axis;
    int y_axis;
} Speed2D;

Speed2D* Speed2D_init(int x_axis, int y_axis);

void Speed2D_del(Speed2D* param);


typedef struct {
    Point2D* position;
    Box2D* box;
    Speed2D* speed;
    bool has_gravity;
} Object2D;

Object2D* Object2D_init(Point2D* position, Box2D* box, Speed2D* speed, bool has_gravity);

Object2D* Object2D_init_2(int x_pos, int y_pos, int width, int height, int x_speed,
                          int y_speed, bool has_gravity);

void Object2D_del(Object2D* param);
