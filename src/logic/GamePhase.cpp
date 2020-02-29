#include "GamePhase.h"
#include "../settings/Inputs.h"
#include "../settings/Phases.h"


#define SPEED 5


GamePhase::GamePhase(string name) {
    this->name = name;

    Phase phase = load_phase(this->name);

    this->player = phase.load_player();
    this->enemies = phase.load_enemies();
    this->scenario = phase.load_scenario();
}


GamePhase::~GamePhase() {}


tuple<int, int> GamePhase::process_key_input(map<string, bool> keys) {
    int new_x_speed = (-1)*SPEED*keys[INPUT_KEY_LEFT] + SPEED*keys[INPUT_KEY_RIGHT];
    int new_y_speed = (-1)*SPEED*keys[INPUT_KEY_UP] + SPEED*keys[INPUT_KEY_DOWN];

    return tuple<int, int>{new_x_speed, new_y_speed};
}


list<tuple<Point2D, Point2D, Object2DType>> GamePhase::update(map<string, bool> keys) {
    list<tuple<Point2D, Point2D, Object2DType>> ret;

    tuple<int, int> processed_key_input = this->process_key_input(keys);

    this->player->x_speed = get<0>(processed_key_input);
    this->player->y_speed = get<1>(processed_key_input);

    this->player->move();

    for(list<Object2D*>::iterator it=this->scenario.begin(); it != this->scenario.end(); it++) {
        Object2D* scenario_object = *it;
        ret.push_back(scenario_object->get_drawing_contour());
    }

    for(list<Object2D*>::iterator it=this->enemies.begin(); it != this->enemies.end(); it++) {
        Object2D* enemy = *it;
        ret.push_back(enemy->get_drawing_contour());
    }

    ret.push_back(this->player->get_drawing_contour());

    return ret;
}
