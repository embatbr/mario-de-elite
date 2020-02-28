#include "GamePhase.h"
#include "../settings/Inputs.h"
#include "../settings/Phases.h"


#define SPEED 5


GamePhase::GamePhase(string name) {
    this->name = name;

    Phase phase = load_phase(this->name);

    this->player = phase.load_player();
}


GamePhase::~GamePhase() {}


tuple<int, int> GamePhase::process_key_input(map<string, bool> keys) {
    int new_x_speed = (-1)*SPEED*keys[INPUT_KEY_LEFT] + SPEED*keys[INPUT_KEY_RIGHT];
    int new_y_speed = (-1)*SPEED*keys[INPUT_KEY_UP] + SPEED*keys[INPUT_KEY_DOWN];

    return tuple<int, int>{new_x_speed, new_y_speed};
}


tuple<Point2D, Point2D> GamePhase::update(map<string, bool> keys) {
    tuple<int, int> processed_key_input = this->process_key_input(keys);

    this->player->x_speed = get<0>(processed_key_input);
    this->player->y_speed = get<1>(processed_key_input);

    this->player->move();

    return this->player->get_drawing_points();
}
