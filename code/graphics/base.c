#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "../logging.h"


const char* IMAGES_DIRPATH = "resources/images";
const int FILEPATH_MAX_LENGTH = 100;


GraphicObject* GraphicObject_init(const char* filename){
    GraphicObject *ret = malloc(sizeof(GraphicObject));

    char* filepath = malloc(sizeof(char) * FILEPATH_MAX_LENGTH);
    snprintf(filepath, FILEPATH_MAX_LENGTH, "%s/%s", IMAGES_DIRPATH, filename);

    ret->image = al_load_bitmap(filepath);
    if(!ret->image) {
        print_error("failed to load image.");
        exit(-1);
    }

    return ret;
}
