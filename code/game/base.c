#include <stdlib.h>

#include "base.h"


GameObject* GameObject_init(Object2D* object2d, const char* filename) {
    GameObject* ret = malloc(sizeof(GameObject));

    ret->object2d = object2d;
    ret->graphic_object = GraphicObject_init(filename);

    return ret;
}


// TODO remove the fixed positions (tests only)
GameScenario* GameScenario_init(int num_game_objects) {
    GameScenario* ret = malloc(sizeof(GameScenario));

    ret->num_game_objects = num_game_objects;
    ret->game_objects = malloc(sizeof(GameObject*) * ret->num_game_objects);

    for(int i = 0; i < ret->num_game_objects; i++) {
        Object2D* object2d = Object2D_init_2(100*(i + 1), 400 - 50*i, 128,
                                                   32, 0, 0, false);
        *(ret->game_objects + i) = GameObject_init(object2d, "scenario/block-4w.png");
    }

    return ret;
}


GamePlay* GamePlay_init(Screen* screen, GraphicObject* background, GameScenario* scenario,
                        GameObject* mario, Point2D* mouse_position) {
    GamePlay* ret = malloc(sizeof(GamePlay));

    ret->screen = screen;
    ret->background = background;
    ret->scenario = scenario;
    ret->mario = mario;
    ret->mouse_position = mouse_position;

    return ret;
}
