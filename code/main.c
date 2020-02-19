#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "physics/base.h"
#include "game/base.h"
#include "game/logic.h"
#include "graphics/base.h"
#include "graphics/drawing.h"
#include "logging.h"


const float FPS = 25;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MARIO_WIDTH = 32;
const int MARIO_HEIGHT = 42;
const int NUM_BLOCKS = 5;


typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
} AllegroDevices;


int DRAW_FLAGS = 0;


/**
Initialize Allegro and all devices associated (keyboards, timers, displays...).
*/
int init_allegro_devices(AllegroDevices* allegro_devices) {
    if(!al_init()) {
        print_error("failed to initialize allegro!");
        return -1;
    }

    if(!al_init_primitives_addon()) {
        print_error("failed to initialize `al_init_primitives_addon`!");
        return -1;
    }

    if(!al_init_image_addon()) {
        print_error("failed to initialize `al_init_image_addon`!");
        return -1;
    }

    if(!al_install_keyboard()) {
        print_error("failed to initialize the keyboard!");
        return -1;
    }

    if(!al_install_mouse()) {
        print_error("failed to initialize the mouse!");
        return -1;
    }

    allegro_devices->timer = al_create_timer(1.0 / FPS);
    if(!allegro_devices->timer) {
        print_error("failed to create timer!");
        return -1;
    }

    allegro_devices->event_queue = al_create_event_queue();
    if(!allegro_devices->event_queue) {
        print_error("failed to create event_queue!");
        al_destroy_timer(allegro_devices->timer);
        return -1;
    }

    return 0;
}

void deinit_allegro_devices(AllegroDevices* allegro_devices) {
    al_destroy_timer(allegro_devices->timer);
    al_destroy_event_queue(allegro_devices->event_queue);
}


void register_events_sources(AllegroDevices* allegro_devices, GamePlay* game_play) {
    al_register_event_source(
        allegro_devices->event_queue,
        al_get_display_event_source(game_play->screen->display)
    );

    al_register_event_source(
        allegro_devices->event_queue,
        al_get_timer_event_source(allegro_devices->timer)
    );

    al_register_event_source(
        allegro_devices->event_queue,
        al_get_keyboard_event_source()
    );

    al_register_event_source(
        allegro_devices->event_queue,
        al_get_mouse_event_source()
    );
}


void main_loop(AllegroDevices* allegro_devices, GamePlay* game_play) {
    bool paused = false;
    bool redraw = true;

    draw_game_play(game_play, DRAW_FLAGS);

    al_start_timer(allegro_devices->timer);

    while(1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(allegro_devices->event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(!paused) {
                if(game_play->mario->object2d->position->x_axis < 0 || game_play->mario->object2d->position->x_axis >  SCREEN_WIDTH - MARIO_WIDTH) {
                    game_play->mario->object2d->speed->x_axis = -game_play->mario->object2d->speed->x_axis;
                }

                if(game_play->mario->object2d->position->y_axis < 0 || game_play->mario->object2d->position->y_axis > SCREEN_HEIGHT - MARIO_HEIGHT) {
                    game_play->mario->object2d->speed->y_axis = -game_play->mario->object2d->speed->y_axis;
                }

                game_play->mario->object2d->position->x_axis += game_play->mario->object2d->speed->x_axis;
                game_play->mario->object2d->position->y_axis += game_play->mario->object2d->speed->y_axis;

                game_play->mario->object2d->speed->x_axis = 0;
                game_play->mario->object2d->speed->y_axis = 0;
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
                game_play->mario->object2d->speed->x_axis = -10;
            }
            else if(!paused && ev.keyboard.keycode == 4) { // RIGHT
                game_play->mario->object2d->speed->x_axis = 10;
            }
            else if(!paused && ev.keyboard.keycode == 23) { // UP
                game_play->mario->object2d->speed->y_axis = -10;
            }
            else if(!paused && ev.keyboard.keycode == 19) { // DOWN
                game_play->mario->object2d->speed->y_axis = 10;
            }
        }
        else if(!paused && (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ||
                            ev.type == ALLEGRO_EVENT_MOUSE_AXES)) {
            game_play->mouse_position->x_axis = ev.mouse.x;
            game_play->mouse_position->y_axis = ev.mouse.y;

            if(ev.mouse.x < (game_play->mario->object2d->position->x_axis + MARIO_WIDTH/2)) {
                DRAW_FLAGS = DRAW_FLAGS | ALLEGRO_FLIP_HORIZONTAL;
            }
            else if(DRAW_FLAGS & ALLEGRO_FLIP_HORIZONTAL == ALLEGRO_FLIP_HORIZONTAL){
                DRAW_FLAGS = DRAW_FLAGS ^ ALLEGRO_FLIP_HORIZONTAL;
            }
        }
        else if(!paused && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            game_play->mario->object2d->position->x_axis = ev.mouse.x;
            game_play->mario->object2d->position->y_axis = ev.mouse.y;
        }

        if(redraw && al_is_event_queue_empty(allegro_devices->event_queue)) {
            redraw = false;
            draw_game_play(game_play, DRAW_FLAGS);
        }
    }
}


GamePlay* init_game() {
    return GamePlay_init(
        Screen_init(SCREEN_WIDTH, SCREEN_HEIGHT),
        GraphicObject_init("backgrounds/05.png"),
        GameScenario_init(NUM_BLOCKS),
        GameObject_init(
            Object2D_init_2(100, 100, MARIO_WIDTH, MARIO_HEIGHT, 0, 0, true),
            "mario.png"
        ),
        Point2D_init(100, 100)
    );
}


int main(int argc, char** argv) {
    AllegroDevices* allegro_devices = malloc(sizeof(AllegroDevices));

    if(init_allegro_devices(allegro_devices) != 0) {
        return -1;
    }

    GamePlay* game_play = init_game();
    register_events_sources(allegro_devices, game_play);

    main_loop(allegro_devices, game_play);

    deinit_allegro_devices(allegro_devices);

    return 0;
}
