#include <allegro5/allegro_primitives.h>

#include "logic.h"
#include "building.h"

#include "../graphics/drawing.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MARIO_WIDTH = 32;
const int MARIO_HEIGHT = 42;


void draw_game_play(GamePlay* game_play, const int mario_draw_flags) {
    Screen* screen = game_play->screen;
    GraphicObject* background = game_play->background;
    GameScenario* scenario = game_play->scenario;
    SpritedGameObject* mario = game_play->mario;

    // reset canvas
    clear_screen(screen);

    // draw on canvas
    paint_screen(screen, background, 0, 0, 0);

    for(int i = 0; i < scenario->num_game_objects; i++) {
        GameObject* game_object = *(scenario->game_objects + i);
        Point2D* position = game_object->object2d->position;
        Box2D* collision_box = game_object->object2d->collision_box;

        int x_left_sup = position->x_axis;
        int y_left_sup = position->y_axis;
        int x_right_inf = position->x_axis + collision_box->width;
        int y_right_inf = position->y_axis + collision_box->height;

        al_draw_filled_rectangle(x_left_sup, y_left_sup, x_right_inf, y_right_inf,
            BASE_COLOR_RED);
    }

    Point2D* position = mario->game_object->object2d->position;
    paint_screen(screen, mario->graphic_object, position->x_axis, position->y_axis,
                 mario_draw_flags);

    // // TODO for testing purposes only
    // al_draw_filled_circle(mouse_position->x_axis, mouse_position->y_axis, 5, BASE_COLOR_BLACK);
    // al_draw_circle(mouse_position->x_axis, mouse_position->y_axis, 15, BASE_COLOR_BLACK, 2);

    // show on display
    update_screen(screen);
}


void main_loop(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* event_queue, GamePlay* game_play) {
    Screen* screen = game_play->screen;
    SpritedGameObject* mario = game_play->mario;

    bool paused = false;
    bool redraw = true;
    int mario_draw_flags = 0;

    draw_game_play(game_play, mario_draw_flags);

    al_start_timer(timer);

    while(1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(!paused) {
                if(game_play->mario->game_object->object2d->position->x_axis < 0 ||
                   game_play->mario->game_object->object2d->position->x_axis >  screen->width -
                   mario->game_object->object2d->collision_box->width) {
                    game_play->mario->game_object->object2d->speed->x_axis = -game_play->mario->game_object->object2d->speed->x_axis;
                }

                if(game_play->mario->game_object->object2d->position->y_axis < 0 ||
                   game_play->mario->game_object->object2d->position->y_axis > screen->height -
                   mario->game_object->object2d->collision_box->height) {
                    game_play->mario->game_object->object2d->speed->y_axis = -game_play->mario->game_object->object2d->speed->y_axis;
                }

                game_play->mario->game_object->object2d->position->x_axis += game_play->mario->game_object->object2d->speed->x_axis;
                game_play->mario->game_object->object2d->position->y_axis += game_play->mario->game_object->object2d->speed->y_axis;

                game_play->mario->game_object->object2d->speed->x_axis = 0;
                game_play->mario->game_object->object2d->speed->y_axis = 0;
            }

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            // printf("%d\n", ev.keyboard.keycode);

            if(ev.keyboard.keycode == 67) { // ENTER
                paused = !paused;
            }
            else if(ev.keyboard.keycode == 59) { // ESC
                break;
            }
            else if(!paused && ev.keyboard.keycode == 1) { // LEFT
                game_play->mario->game_object->object2d->speed->x_axis = -10;
            }
            else if(!paused && ev.keyboard.keycode == 4) { // RIGHT
                game_play->mario->game_object->object2d->speed->x_axis = 10;
            }
            else if(!paused && ev.keyboard.keycode == 23) { // UP
                game_play->mario->game_object->object2d->speed->y_axis = -10;
            }
            else if(!paused && ev.keyboard.keycode == 19) { // DOWN
                game_play->mario->game_object->object2d->speed->y_axis = 10;
            }
        }
        else if(!paused && (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ||
                            ev.type == ALLEGRO_EVENT_MOUSE_AXES)) {
            game_play->mouse_position->x_axis = ev.mouse.x;
            game_play->mouse_position->y_axis = ev.mouse.y;

            if(ev.mouse.x < (game_play->mario->game_object->object2d->position->x_axis +
               mario->game_object->object2d->collision_box->width/2)) {
                mario_draw_flags = mario_draw_flags | ALLEGRO_FLIP_HORIZONTAL;
            }
            else if(mario_draw_flags & ALLEGRO_FLIP_HORIZONTAL == ALLEGRO_FLIP_HORIZONTAL){
                mario_draw_flags = mario_draw_flags ^ ALLEGRO_FLIP_HORIZONTAL;
            }
        }
        else if(!paused && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            game_play->mario->game_object->object2d->position->x_axis = ev.mouse.x;
            game_play->mario->game_object->object2d->position->y_axis = ev.mouse.y;
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            draw_game_play(game_play, mario_draw_flags);
        }
    }
}


GamePlay* create_game() {
    GameScenario* game_scenario = build_game_scenario("phase-01");

    return GamePlay_init(
        Screen_init(SCREEN_WIDTH, SCREEN_HEIGHT),
        GraphicObject_init("backgrounds/01.png"),
        game_scenario,
        SpritedGameObject_init(
            Object2D_init_2(100, 100, MARIO_WIDTH, MARIO_HEIGHT, 0, 0, true),
            "player/mario.png"
        ),
        Point2D_init(100, 100)
    );
}
