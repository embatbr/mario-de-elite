#ifndef GRAPHICS_BASE_H
    #define GRAPHICS_BASE_H

    /**
    Base functions and types for the game graphics.
    */

    #include <allegro5/allegro.h>


    #ifndef BASE_COLOR_WHITE
        #define BASE_COLOR_WHITE al_map_rgb(255, 255, 255)
    #endif


    typedef struct {
        ALLEGRO_BITMAP* canvas;
        ALLEGRO_DISPLAY* display;
    } Screen;

    Screen* Screen_init(int width, int height);


    typedef struct {
        ALLEGRO_BITMAP* image;
    } GraphicObject;

    GraphicObject* GraphicObject_init(const char* filename);
#endif
