#pragma once

/**
Functions and types to draw/paint on a canvas.
*/

#include "base.h"


void clear_screen(Screen* screen);

void update_screen(Screen* screen);


void paint_screen(Screen* screen, GraphicObject* graphic_object, int x_axis,
                  int y_axis, int flags);
