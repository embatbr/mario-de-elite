#include <allegro5/allegro_primitives.h>

#include "building.h"
#include "../conf.h"
#include "../controllers/base.h"
#include "../controllers/logic.h"
#include "../graphics/drawing.h"
#include "logic.h"


const int MARIO_X_SPEED = 5;
const int MARIO_Y_SPEED = 15;
const int MARIO_WIDTH = 32;
const int MARIO_HEIGHT = 42;


void draw_game_play(GamePlay* game_play, const int mario_draw_flags) {
    Screen* screen = game_play->screen;
    GraphicObject* background = game_play->background;
    GameScenario* scenario = game_play->scenario;
    SpritedGameObject* mario = game_play->mario;
    Point2D* mouse_position = game_play->mouse_position;

    // reset canvas
    clear_screen(screen);

    // draw on canvas
    paint_screen(screen, background, 0, 0, 0);

    for(int i = 0; i < scenario->num_game_objects; i++) {
        GameObject* game_object = *(scenario->game_objects + i);
        Point2D* position = game_object->object2d->position;
        Box2D* box = game_object->object2d->box;

        int x_left_sup = position->x_axis;
        int y_left_sup = position->y_axis;
        int x_right_inf = position->x_axis + box->width;
        int y_right_inf = position->y_axis + box->height;

        if(game_object->type == GAME_OBJECT_SPRITED) {
            al_draw_rectangle(x_left_sup, y_left_sup, x_right_inf, y_right_inf,
                BASE_COLOR_BLACK, 1);
        }
        else if(game_object->type == GAME_OBJECT_PLATFORM) {
            al_draw_filled_rectangle(x_left_sup, y_left_sup, x_right_inf, y_right_inf,
                BASE_COLOR_RED);
        }
        else if(game_object->type == GAME_OBJECT_BLOCK) {
            al_draw_rectangle(x_left_sup, y_left_sup, x_right_inf, y_right_inf,
                BASE_COLOR_BLUE, 1);
        }
    }

    Point2D* position = mario->game_object->object2d->position;
    Box2D* box = mario->game_object->object2d->box;
    al_draw_rectangle(position->x_axis, position->y_axis, position->x_axis + box->width,
        position->y_axis + box->height, BASE_COLOR_BLACK, 1);
    paint_screen(screen, mario->graphic_object, position->x_axis, position->y_axis,
                 mario_draw_flags);

    al_draw_filled_circle(mouse_position->x_axis, mouse_position->y_axis, 5, BASE_COLOR_BLACK);
    al_draw_circle(mouse_position->x_axis, mouse_position->y_axis, 15, BASE_COLOR_BLACK, 2);

    // show on display
    update_screen(screen);
}


void main_loop(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* event_queue, GamePlay* game_play) {
    Screen* screen = game_play->screen;
    SpritedGameObject* mario = game_play->mario;
    Keyboard* keyboard = game_play->keyboard;

    Point2D* mario_position = game_play->mario->game_object->object2d->position;
    Box2D* mario_box = game_play->mario->game_object->object2d->box;
    Speed2D* mario_speed = game_play->mario->game_object->object2d->speed;
    mario_speed->x_axis = mario_speed->y_axis = 0;

    bool running = true;
    int mario_draw_flags = 0;

    draw_game_play(game_play, mario_draw_flags);

    al_start_timer(timer);

    while(1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(running) {
                mario_speed->x_axis = MARIO_X_SPEED * direction_h(keyboard);
                mario_speed->y_axis = MARIO_Y_SPEED * direction_v(keyboard);

                mario_position->x_axis += mario_speed->x_axis;
                mario_position->y_axis += mario_speed->y_axis;

                if(mario_position->x_axis < 0) {
                    mario_position->x_axis = 0;
                }
                else if(mario_position->x_axis > screen->width - mario_box->width) {
                    mario_position->x_axis = screen->width - mario_box->width;
                }

                if(mario_position->y_axis < 0) {
                    mario_position->y_axis = 0;
                }
                else if(mario_position->y_axis > screen->height - mario_box->height) {
                    mario_position->y_axis = screen->height - mario_box->height;
                }

                mario_speed->x_axis = 0;
                mario_speed->y_axis = 0;
            }

            draw_game_play(game_play, mario_draw_flags); // updates canvas even when paused
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP) {
            bool key_is_down = ev.type == ALLEGRO_EVENT_KEY_DOWN;

            if(key_is_down && ev.keyboard.keycode == KEY_EXIT) {
                break;
            }
            if(key_is_down && ev.keyboard.keycode == KEY_PAUSE) {
                running = !running;
            }

            if(ev.keyboard.keycode == KEY_LEFT) {
                keyboard->key_left_pressed = key_is_down;
            }
            if(ev.keyboard.keycode == KEY_RIGHT) {
                keyboard->key_right_pressed = key_is_down;
            }
            if(ev.keyboard.keycode == KEY_UP) {
                keyboard->key_up_pressed = key_is_down;
            }
            if(ev.keyboard.keycode == KEY_DOWN) {
                keyboard->key_down_pressed = key_is_down;
            }
        }

        if(running && ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            game_play->mouse_position->x_axis = ev.mouse.x;
            game_play->mouse_position->y_axis = ev.mouse.y;

            if(ev.mouse.x < (mario_position->x_axis +
               mario->game_object->object2d->box->width/2)) {
                mario_draw_flags = mario_draw_flags | ALLEGRO_FLIP_HORIZONTAL;
            }
            else if(mario_draw_flags & ALLEGRO_FLIP_HORIZONTAL == ALLEGRO_FLIP_HORIZONTAL){
                mario_draw_flags = mario_draw_flags ^ ALLEGRO_FLIP_HORIZONTAL;
            }
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
        Point2D_init(100, 100),
        Keyboard_init()
    );
}
