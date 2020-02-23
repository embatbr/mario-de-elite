#pragma once

/**
Contains the logic for controlling.
*/

#include "base.h"


void capture_keyboard_event(ALLEGRO_EVENT ev, Keyboard* keyboard);

int direction_h(Keyboard* keyboard);

int direction_v(Keyboard* keyboard);


void capture_mouse_event(ALLEGRO_EVENT ev, Mouse* mouse);
