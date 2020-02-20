#include <stdio.h>
#include <stdlib.h>

#include "building.h"


const char* RESOURCES_GAME_DIRPATH = "resources/game";


GameScenario* build_game_scenario(const char* phase) {
    const int FILEPATH_MAX_LENGTH = 100;
    const int LINE_MAX_LENGTH = 100;

    char line[LINE_MAX_LENGTH];

    char* filepath = malloc(sizeof(char) * FILEPATH_MAX_LENGTH);
    snprintf(filepath, FILEPATH_MAX_LENGTH, "%s/%s", RESOURCES_GAME_DIRPATH, phase);

    char* stage = "reading file";

    int num_game_objects = -1;
    int game_object_count = 0;
    int num_platforms = -1;
    int platform_count = 0;
    int num_blocks = -1;
    int block_count = 0;
    GameObject** game_objects = NULL;

    FILE *file = fopen(filepath, "r");
    if(file != NULL) {
        if(fgets(line, LINE_MAX_LENGTH, file) != NULL) {
            num_game_objects = atoi(line);
            game_objects = malloc(sizeof(GameObject*) * num_game_objects);
        }

        while(fgets(line, LINE_MAX_LENGTH, file) != NULL) {
            int i = 0;
            while(line[i] != '\n') {
                line[i] = line[i];
                i++;
            }
            line[i] = 0;

            if(strcmp(stage, "reading file") == 0 && strcmp(line, "platforms") == 0) {
                stage = "reading number of platforms";
            }
            else if(strcmp(stage, "reading number of platforms") == 0) {
                stage = "reading platforms";
                num_platforms = atoi(line);
            }
            else if(strcmp(stage, "reading platforms") == 0) {
                int x_pos = atoi(strtok(line, " "));
                int y_pos = atoi(strtok(NULL, " "));
                int width = atoi(strtok(NULL, " "));

                Object2D* object2d = Object2D_init_2(x_pos, y_pos, width, 1, 0, 0, false);
                *(game_objects + game_object_count) = GameObject_init(object2d);

                game_object_count++;
                platform_count++;
                if(platform_count == num_platforms) {
                    stage = "reading file";
                }
            }
            else if(strcmp(stage, "reading file") == 0 && strcmp(line, "blocks") == 0) {
                stage = "reading number of blocks";
            }
            else if(strcmp(stage, "reading number of blocks") == 0) {
                stage = "reading blocks";
                num_blocks = atoi(line);
            }
            else if(strcmp(stage, "reading blocks") == 0) {
                int x_pos = atoi(strtok(line, " "));
                int y_pos = atoi(strtok(NULL, " "));
                int width = atoi(strtok(NULL, " "));
                int height = atoi(strtok(NULL, " "));

                Object2D* object2d = Object2D_init_2(x_pos, y_pos, width, height, 0, 0, false);
                *(game_objects + game_object_count) = GameObject_init(object2d);

                game_object_count++;
                block_count++;
                if(block_count == num_blocks) {
                    stage = "reading file";
                }
            }
        }

        fclose(file);
    }

    return GameScenario_init(num_game_objects, game_objects);
}