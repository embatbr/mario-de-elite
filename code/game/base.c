#include <stdlib.h>

#include "base.h"


GameObject* GameObject_init(Object2D* physical_object) {
    GameObject *ret = malloc(sizeof(GameObject));

    ret->physical_object = physical_object;

    return ret;
}
