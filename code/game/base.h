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
    // TODO add enum to classify as platform, wall, block, player and etc...
} GameObject;

GameObject* GameObject_init(Object2D* object2d);


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
