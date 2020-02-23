#pragma once

/**
Contains the logic for the game execution (main loop, drawing scenario and etc.).
*/

#include "base.h"


GamePlay* create_game();


void main_loop(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* event_queue, GamePlay* game_play);
