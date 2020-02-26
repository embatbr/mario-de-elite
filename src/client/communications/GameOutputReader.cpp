#include "GameOutputReader.h"


GameOutputReader::GameOutputReader() {}


GameOutputReader::~GameOutputReader() {}


list<int> GameOutputReader::read(list<string> output) {
    list<int> ret;

    while(!output.empty()) {
        int output_token = stoi(output.front());
        ret.push_back(output_token);

        output.pop_front();
    }

    return ret;
}
