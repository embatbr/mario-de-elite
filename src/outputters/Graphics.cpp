#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Graphics.h"


#define BASE_COLOR_WHITE al_map_rgb(255, 255, 255)
#define BASE_COLOR_BLACK al_map_rgb(0, 0, 0)
#define BASE_COLOR_RED al_map_rgb(255, 0, 0)
#define BASE_COLOR_GREEN al_map_rgb(0, 255, 0)
#define BASE_COLOR_BLUE al_map_rgb(0, 0, 255)


Graphics::Graphics() {}


Graphics::~Graphics() {}


ALLEGRO_COLOR get_object_color(Object2DType object_type) {
    switch(object_type) {
        case OBJECT_PLATFORM:
            return BASE_COLOR_GREEN;
        case OBJECT_BLOCK:
            return BASE_COLOR_BLACK;
        case OBJECT_ENEMY:
            return BASE_COLOR_RED;
        case OBJECT_PLAYER:
            return BASE_COLOR_BLUE;
    }
}


void Graphics::draw_contour(list<tuple<Point2D, Point2D, Object2DType>> cur_state) {
    al_clear_to_color(BASE_COLOR_WHITE);

    for(list<tuple<Point2D, Point2D, Object2DType>>::iterator it=cur_state.begin();
                it != cur_state.end(); it++) {
        tuple<Point2D, Point2D, Object2DType> info = *it;

        Point2D sup_left = get<0>(info);
        Point2D inf_right = get<1>(info);
        Object2DType object_type = get<2>(info);

        al_draw_rectangle(sup_left.x_axis, sup_left.y_axis, inf_right.x_axis,
            inf_right.y_axis, get_object_color(object_type), 1);
    }

    al_flip_display();
}
