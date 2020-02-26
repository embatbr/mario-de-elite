#pragma once


#include <list>
#include <string>
using namespace std;


class GameOutputReader {
public:
    GameOutputReader();
    ~GameOutputReader();

    list<int> read(list<string> output);
};
