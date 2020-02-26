#pragma once

/**
Read a formatted input that a server receives from a client.
*/

#include <list>
#include <string>
using namespace std;


class GameInputReader {
    public:
        GameInputReader();
        ~GameInputReader();

        list<int> read(string input);
};
