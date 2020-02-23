#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "../conf.h"
#include "../logging.h"


Screen* Screen_init(int width, int height) {
    Screen* ret = malloc(sizeof(Screen));

    ret->width = width;
    ret->height = height;

    ret->canvas = al_create_bitmap(ret->width, ret->height);
    if(!ret->canvas) {
        print_error("failed to create canvas.");
        exit(-1);
    }

    ret->display = al_create_display(ret->width, ret->height);
    if(!ret->display) {
        print_error("failed to create display.");
        exit(-1);
    }

    return ret;
}

void Screen_del(Screen* param) {
    al_destroy_bitmap(param->canvas);
    al_destroy_display(param->display);
    free(param);
}


GraphicObject* GraphicObject_init(const char* filename){
    GraphicObject* ret = malloc(sizeof(GraphicObject));

    char* filepath = malloc(sizeof(char) * FILEPATH_MAX_LENGTH);
    snprintf(filepath, FILEPATH_MAX_LENGTH, "%s/%s", IMAGES_DIRPATH, filename);

    ret->image = al_load_bitmap(filepath);
    if(!ret->image) {
        print_error("failed to load image.");
        exit(-1);
    }

    ret->flags = 0;

    return ret;
}

void GraphicObject_del(GraphicObject* param) {
    al_destroy_bitmap(param->image);
    free(param);
}
