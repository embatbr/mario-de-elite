#pragma once

/**
Contains the logic for the game execution (main loop, drawing scenario and etc.).
*/

#include "base.h"


void draw_game_play(GamePlay* game_play, const int mario_draw_flags);


void main_loop(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* event_queue, GamePlay* game_play);


GamePlay* create_game();
