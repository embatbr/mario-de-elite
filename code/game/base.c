#include <stdlib.h>

#include "base.h"


GameObject* GameObject_init(Object2D* object2d, GameObjectType type) {
    GameObject* ret = malloc(sizeof(GameObject));

    ret->object2d = object2d;
    ret->type = type;

    return ret;
}


SpritedGameObject* SpritedGameObject_init(Object2D* object2d, const char* filename) {
    SpritedGameObject* ret = malloc(sizeof(SpritedGameObject));

    ret->game_object = GameObject_init(object2d, GAME_OBJECT_SPRITED);
    ret->graphic_object = GraphicObject_init(filename);

    return ret;
}


// TODO remove the fixed positions (tests only)
GameScenario* GameScenario_init(int num_game_objects, GameObject** game_objects) {
    GameScenario* ret = malloc(sizeof(GameScenario));

    ret->num_game_objects = num_game_objects;
    ret->game_objects = game_objects;

    return ret;
}


GamePlay* GamePlay_init(Screen* screen, GraphicObject* background, GameScenario* scenario,
                        SpritedGameObject* mario, Point2D* mouse_position) {
    GamePlay* ret = malloc(sizeof(GamePlay));

    ret->screen = screen;
    ret->background = background;
    ret->scenario = scenario;
    ret->mario = mario;
    ret->mouse_position = mouse_position;

    return ret;
}
