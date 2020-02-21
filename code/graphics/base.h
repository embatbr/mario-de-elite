#pragma once

/**
Base functions and types for the game graphics.
*/

#include <allegro5/allegro.h>


#define BASE_COLOR_WHITE al_map_rgb(255, 255, 255)
#define BASE_COLOR_BLACK al_map_rgb(0, 0, 0)
#define BASE_COLOR_RED al_map_rgb(255, 0, 0)
#define BASE_COLOR_GREEN al_map_rgb(0, 255, 0)
#define BASE_COLOR_BLUE al_map_rgb(0, 0, 255)


typedef struct {
    int width;
    int height;
    ALLEGRO_BITMAP* canvas;
    ALLEGRO_DISPLAY* display;
} Screen;

Screen* Screen_init(int width, int height);


typedef struct {
    ALLEGRO_BITMAP* image;
    int flags;
} GraphicObject;

GraphicObject* GraphicObject_init(const char* filename);
