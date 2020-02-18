/**
Functions and types basic for the game (e.g., collision boxes).
*/

#include <stdbool.h>


typedef struct {
    int x_axis;
    int y_axis;
} Point2D;

Point2D* Point2D_init(int x_axis, int y_axis);


typedef struct {
    int width;
    int height;
} Box2D;

Box2D* Box2D_init(int width, int height);


typedef struct {
    int x_axis;
    int y_axis;
} Speed2D;

Speed2D* Speed2D_init(int x_axis, int y_axis);


typedef struct {
    Point2D* position;
    Box2D* collision_box;
    Speed2D* speed;
    bool has_gravity;
} Object2D;

Object2D* Object2D_init(Point2D* position, Box2D* collision_box, Speed2D* speed,
                        bool has_gravity);

Object2D* Object2D_init_2(int x_pos, int y_pos, int width, int height, int x_speed,
                          int y_speed, bool has_gravity);
