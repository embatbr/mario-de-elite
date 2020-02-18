/**
Base functions and types for the game (e.g., game objects).
*/

#include <allegro5/allegro.h>

#include "../physics/base.h"


typedef struct {
    Object2D* physical_object;
    ALLEGRO_BITMAP* image;
} GameObject;

GameObject* GameObject_init(Object2D* physical_object);
