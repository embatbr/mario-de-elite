#include <bits/stdc++.h>

#include "GameInputReader.h"


GameInputReader::GameInputReader() {}


GameInputReader::~GameInputReader() {}


list<int> GameInputReader::read(string input) {
    list<int> tokens;

    stringstream input_splitted = stringstream(input);
    string token;
    input_splitted >> token;
    if(token.compare("directional") == 0) {
        while(input_splitted >> token) {
            tokens.push_back(stoi(token));
        }
    }

    return tokens;
}
