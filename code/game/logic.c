#include "logic.h"

#include "../graphics/drawing.h"


void draw_game_play(GamePlay* game_play, const int MARIO_DRAW_FLAGS) {
    Screen* screen = game_play->screen;
    GraphicObject* background = game_play->background;
    GameScenario* scenario = game_play->scenario;
    GameObject* mario = game_play->mario;

    // reset canvas
    clear_screen(screen);

    // draw on canvas
    paint_screen(screen, background, 0, 0, 0);

    for(int i = 0; i < scenario->num_game_objects; i++) {
        GameObject* block = *(scenario->game_objects + i);
        Point2D* position = block->object2d->position;

        paint_screen(screen, block->graphic_object, position->x_axis, position->y_axis, 0);
    }

    Point2D* position = mario->object2d->position;
    paint_screen(screen, mario->graphic_object, position->x_axis, position->y_axis,
                 MARIO_DRAW_FLAGS);

    // // TODO for testing purposes only
    // al_draw_filled_circle(mouse_position->x_axis, mouse_position->y_axis, 5, BASE_COLOR_BLACK);
    // al_draw_circle(mouse_position->x_axis, mouse_position->y_axis, 15, BASE_COLOR_BLACK, 2);

    // show on display
    update_screen(screen);
}
