#include "GameOutputWriter.h"


GameOutputWriter::GameOutputWriter() {}


GameOutputWriter::~GameOutputWriter() {}


// void GameOutputWriter::write(Point2D* player) {
list<string> GameOutputWriter::write(Point2D* player, int width, int height) {
    list<string> output;

    output.push_back(to_string(player->x_axis));
    output.push_back(to_string(player->y_axis));
    output.push_back(to_string(width));
    output.push_back(to_string(height));

    return output;
}
