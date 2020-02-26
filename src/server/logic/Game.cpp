#include <list>

#include "Game.h"
#include "../communications/GameInputReader.h"
#include "../communications/GameOutputWriter.h"
#include "../../common/InputKey.h"


#define SPEED 5


Game::Game() {
    this->player = new Point2D(100, 100);
    this->width = 20;
    this->height = 35;
    this->x_speed = 0;
    this->y_speed = 0;
}


Game::~Game() {
}


list<string> Game::run(string input) {
    GameInputReader* game_input_reader = new GameInputReader();

    list<int> tokens = game_input_reader->read(input);
    while(!tokens.empty()) {
        int token = tokens.front();

        if(token == INPUT_KEY_LEFT) {
            this->x_speed = this->x_speed - SPEED;
        }
        if(token == INPUT_KEY_RIGHT) {
            this->x_speed = this->x_speed + SPEED;
        }
        if(token == INPUT_KEY_UP) {
            this->y_speed = this->y_speed - SPEED;
        }
        if(token == INPUT_KEY_DOWN) {
            this->y_speed = this->y_speed + SPEED;
        }

        tokens.pop_front();
    }


    this->player->move(this->x_speed, this->y_speed);

    this->x_speed = 0;
    this->y_speed = 0;

    GameOutputWriter* game_output_writer = new GameOutputWriter();
    return game_output_writer->write(this->player, this->width, this->height);
}
