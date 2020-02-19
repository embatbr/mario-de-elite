#pragma once

/**
Base functions and types for the game (e.g., game objects).
*/

#ifndef PHYSICS_BASE_H
    #include "../physics/base.h"
#endif
#ifndef GRAPHICS_BASE_H
    #include "../graphics/base.h"
#endif


typedef struct {
    Object2D* object2d;
    GraphicObject* graphic_object;
} GameObject;

GameObject* GameObject_init(Object2D* object2d, const char* filename);
