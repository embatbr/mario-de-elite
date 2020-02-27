#include "Game.h"
#include "../settings/Inputs.h"


#define SPEED 5


Game::Game() {
    this->player = new Box2D(100, 100, 20, 35);
}


Game::~Game() {}


tuple<int, int> Game::process_key_input(map<string, bool> keys) {
    int new_x_speed = (-1)*SPEED*keys[INPUT_KEY_LEFT] + SPEED*keys[INPUT_KEY_RIGHT];
    int new_y_speed = (-1)*SPEED*keys[INPUT_KEY_UP] + SPEED*keys[INPUT_KEY_DOWN];

    return tuple<int, int>{new_x_speed, new_y_speed};
}


void Game::update(map<string, bool> keys) {
    tuple<int, int> processed_key_input = this->process_key_input(keys);

    int x_speed = get<0>(processed_key_input);
    int y_speed = get<1>(processed_key_input);

    this->player->move(x_speed, y_speed);
}
