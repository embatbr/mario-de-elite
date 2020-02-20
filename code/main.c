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


ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* event_queue;


/**
Initialize Allegro and all devices associated (keyboards, timers, displays...).
*/
int init_allegro_devices() {
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

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        print_error("failed to create timer!");
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        print_error("failed to create event_queue!");
        al_destroy_timer(timer);
        return -1;
    }

    return 0;
}

void deinit_allegro_devices() {
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}


void register_events_sources(GamePlay* game_play) {
    al_register_event_source(
        event_queue,
        al_get_display_event_source(game_play->screen->display)
    );

    al_register_event_source(
        event_queue,
        al_get_timer_event_source(timer)
    );

    al_register_event_source(
        event_queue,
        al_get_keyboard_event_source()
    );

    al_register_event_source(
        event_queue,
        al_get_mouse_event_source()
    );
}


int main(int argc, char** argv) {
    if(init_allegro_devices() != 0) {
        return -1;
    }

    GamePlay* game_play = create_game();
    register_events_sources(game_play);
    main_loop(timer, event_queue, game_play);

    deinit_allegro_devices();

    return 0;
}
