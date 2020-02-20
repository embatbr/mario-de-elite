#pragma once

/**
Contains the logic for controlling.
*/

#include "base.h"


int direction_by_key(bool negative_key, bool positive_key);

int direction_h(Keyboard* keyboard);

int direction_v(Keyboard* keyboard);
