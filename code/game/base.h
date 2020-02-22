#pragma once

/**
Base functions and types for the game (e.g., game objects).
*/

#include "../controllers/base.h"
#include "../graphics/base.h"
#include "../physics/base.h"


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

void GameObject_del(GameObject* param);


typedef struct {
    GameObject* game_object;
    GraphicObject* graphic_object;
} SpritedGameObject;

SpritedGameObject* SpritedGameObject_init(Object2D* object2d, const char* filename);

void SpritedGameObject_del(SpritedGameObject* param);


typedef struct {
    int num_game_objects;
    GameObject** game_objects;
} GameScenario;

GameScenario* GameScenario_init(int num_game_objects, GameObject** game_objects);

void GameScenario_del(GameScenario* param);


typedef enum {
    STARTING,
    RUNNING,
    PAUSED,
    TERMINATED
} GAME_STATE;

typedef struct {
    Screen* screen;
    GraphicObject* background;
    GameScenario* scenario;
    SpritedGameObject* mario;
    Controllers* controllers;
    GAME_STATE state;
} GamePlay;

GamePlay* GamePlay_init(Screen* screen, GraphicObject* background, GameScenario* scenario,
                        SpritedGameObject* mario, Controllers* controllers);

void GamePlay_del(GamePlay* param);
