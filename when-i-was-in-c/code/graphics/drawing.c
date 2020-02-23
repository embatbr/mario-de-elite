// TODO include (probably) the allegro image addon

#include "drawing.h"


void clear_screen(Screen* screen) {
    al_set_target_bitmap(screen->canvas);
    al_clear_to_color(BASE_COLOR_WHITE);
}

void update_screen(Screen* screen) {
    al_set_target_bitmap(al_get_backbuffer(screen->display));
    al_draw_bitmap(screen->canvas, 0, 0, 0);

    al_flip_display();
}


void paint_screen(Screen* screen, GraphicObject* graphic_object, int x_axis,
                  int y_axis, int flags) {
    al_set_target_bitmap(screen->canvas);
    al_draw_bitmap(graphic_object->image, x_axis, y_axis, flags);
}
