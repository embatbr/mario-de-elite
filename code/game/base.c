#include <stdlib.h>

#include "base.h"


GameObject* GameObject_init(Object2D* object2d, const char* filename) {
    GameObject *ret = malloc(sizeof(GameObject));

    ret->object2d = object2d;
    ret->graphic_object = GraphicObject_init(filename);

    return ret;
}
