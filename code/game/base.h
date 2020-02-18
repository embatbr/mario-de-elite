/**
Base functions and types for the game (e.g., game objects).
*/

#include "../physics/base.h"
#include "../graphics/base.h"


typedef struct {
    Object2D* object2d;
    GraphicObject* graphic_object;
} GameObject;

GameObject* GameObject_init(Object2D* object2d, const char* filename);
