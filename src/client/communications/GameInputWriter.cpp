#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

#include "GameInputWriter.h"
#include "../../common/InputKey.h"


GameInputWriter::GameInputWriter(Keyboard* keyboard) {
    this->keyboard = keyboard;
}


GameInputWriter::~GameInputWriter() {}


// void GameInputWriter::read() {
string GameInputWriter::write() {
    map<int, bool> keys = this->keyboard->read();

    string input = "directional";
    if(keys[KEY_LEFT]) {
        input = input + " " + to_string(INPUT_KEY_LEFT);
    }
    if(keys[KEY_RIGHT]) {
        input = input + " " + to_string(INPUT_KEY_RIGHT);
    }
    if(keys[KEY_UP]) {
        input = input + " " + to_string(INPUT_KEY_UP);
    }
    if(keys[KEY_DOWN]) {
        input = input + " " + to_string(INPUT_KEY_DOWN);
    }

    cout << input << endl;

    return input;
}
