/**
Base functions and types for the game graphics.
*/

#include <allegro5/allegro.h>


typedef struct {
    ALLEGRO_BITMAP* image;
} GraphicObject;

GraphicObject* GraphicObject_init(const char* filename);
