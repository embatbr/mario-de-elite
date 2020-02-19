#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "../logging.h"


const char* IMAGES_DIRPATH = "resources/images";
const int FILEPATH_MAX_LENGTH = 100;


Screen* Screen_init(int width, int height) {
    Screen* ret = malloc(sizeof(Screen));

    ret->canvas = al_create_bitmap(width, height);
    if(!ret->canvas) {
        print_error("failed to create canvas.");
        exit(-1);
    }

    ret->display = al_create_display(width, height);
    if(!ret->display) {
        print_error("failed to create display.");
        exit(-1);
    }

    return ret;
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

    return ret;
}
