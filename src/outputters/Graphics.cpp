#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Graphics.h"


#define BASE_COLOR_WHITE al_map_rgb(255, 255, 255)
#define BASE_COLOR_BLACK al_map_rgb(0, 0, 0)


Graphics::Graphics() {}


Graphics::~Graphics() {}


void Graphics::paint_contour(tuple<Point2D, Point2D> points) {
    Point2D sup_left = get<0>(points);
    Point2D inf_right = get<1>(points);

    al_clear_to_color(BASE_COLOR_WHITE);

    al_draw_rectangle(
        sup_left.x_axis,
        sup_left.y_axis,
        inf_right.x_axis,
        inf_right.y_axis,
        BASE_COLOR_BLACK,
        1
    );

    al_flip_display();
}
