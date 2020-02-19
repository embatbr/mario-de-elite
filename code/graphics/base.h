#pragma once

/**
Base functions and types for the game graphics.
*/

#include <allegro5/allegro.h>


#define BASE_COLOR_WHITE al_map_rgb(255, 255, 255)
#define BASE_COLOR_BLACK al_map_rgb(0, 0, 0)


typedef struct {
    ALLEGRO_BITMAP* canvas;
    ALLEGRO_DISPLAY* display;
} Screen;

Screen* Screen_init(int width, int height);


typedef struct {
    ALLEGRO_BITMAP* image;
} GraphicObject;

GraphicObject* GraphicObject_init(const char* filename);
