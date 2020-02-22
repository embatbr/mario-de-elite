#include <stdlib.h>

#include "base.h"


GameObject* GameObject_init(Object2D* object2d, GameObjectType type) {
    GameObject* ret = malloc(sizeof(GameObject));

    ret->object2d = object2d;
    ret->type = type;

    return ret;
}

void GameObject_del(GameObject* param) {
    Object2D_del(param->object2d);
    free(param);
}


SpritedGameObject* SpritedGameObject_init(Object2D* object2d, const char* filename) {
    SpritedGameObject* ret = malloc(sizeof(SpritedGameObject));

    ret->game_object = GameObject_init(object2d, GAME_OBJECT_SPRITED);
    ret->graphic_object = GraphicObject_init(filename);

    return ret;
}

void SpritedGameObject_del(SpritedGameObject* param) {
    GameObject_del(param->game_object);
    GraphicObject_del(param->graphic_object);
    free(param);
}


GameScenario* GameScenario_init(int num_game_objects, GameObject** game_objects,
                                int num_enemies, SpritedGameObject** enemies) {
    GameScenario* ret = malloc(sizeof(GameScenario));

    ret->num_game_objects = num_game_objects;
    ret->game_objects = game_objects;
    ret->num_enemies = num_enemies;
    ret->enemies = enemies;

    return ret;
}

void GameScenario_del(GameScenario* param) {
    for(int i = 0; i < param->num_game_objects; i++) {
        GameObject_del(*(param->game_objects + i));
    }
    free(param->game_objects);
    for(int i = 0; i < param->num_enemies; i++) {
        SpritedGameObject_del(*(param->enemies + i));
    }
    free(param->enemies);
    free(param);
}


GamePlay* GamePlay_init(Screen* screen, GraphicObject* background, GameScenario* scenario,
                        SpritedGameObject* mario, Controllers* controllers) {
    GamePlay* ret = malloc(sizeof(GamePlay));

    ret->screen = screen;
    ret->background = background;
    ret->scenario = scenario;
    ret->mario = mario;
    ret->controllers = controllers;
    ret->state = STARTING;

    return ret;
}

void GamePlay_del(GamePlay* param) {
    Screen_del(param->screen);
    GraphicObject_del(param->background);
    GameScenario_del(param->scenario);
    SpritedGameObject_del(param->mario);
    Controllers_del(param->controllers);
    free(param);
}
