#pragma once

/**
Formats input that a client sends to a server.
*/

#include <string>
using namespace std;

#include "../controllers/Keyboard.h"


class GameInputWriter {
    private:
        Keyboard* keyboard;

    public:
        GameInputWriter(Keyboard* keyboard);
        ~GameInputWriter();

        // void write();
        string write();
};
