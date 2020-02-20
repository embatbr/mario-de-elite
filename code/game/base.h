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


typedef enum {
    GAME_OBJECT_PLATFORM,
    GAME_OBJECT_BLOCK,
    GAME_OBJECT_SPRITED
} GameObjectType;

typedef struct {
    Object2D* object2d;
    GameObjectType type;
} GameObject;

GameObject* GameObject_init(Object2D* object2d, GameObjectType type);


typedef struct {
    GameObject* game_object;
    GraphicObject* graphic_object;
} SpritedGameObject;

SpritedGameObject* SpritedGameObject_init(Object2D* object2d, const char* filename);


typedef struct {
    int num_game_objects;
    GameObject** game_objects;
} GameScenario;

GameScenario* GameScenario_init(int num_game_objects, GameObject** game_objects);


typedef struct {
    Screen* screen;
    GraphicObject* background;
    GameScenario* scenario;
    SpritedGameObject* mario;
    Point2D* mouse_position;
} GamePlay;

GamePlay* GamePlay_init(Screen* screen, GraphicObject* background, GameScenario* scenario,
                        SpritedGameObject* mario, Point2D* mouse_position);
