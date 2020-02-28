#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "base/Object2D.h"
#include "base/Point2D.h"
#include "inputters/Keyboard.h"
#include "settings/Inputs.h"
#include "logic/GamePhase.h"
#include "outputters/Graphics.h"


#define FPS 25
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_TIMER* timer = NULL;


bool init_allegro_devices() {
    if(!al_init()) {
        cout << "failed to initialize allegro!" << endl;
        return false;
    }

    if(!al_init_primitives_addon()) {
        cout << "failed to initialize `al_init_primitives_addon`!" << endl;
        return false;
    }

    // if(!al_init_image_addon()) {
    //     cout << "failed to initialize `al_init_image_addon`!" << endl;
    //     return false;
    // }

    if(!al_install_keyboard()) {
        cout << "failed to initialize the keyboard!" << endl;
        return false;
    }

    if(!al_install_mouse()) {
        cout << "failed to initialize the mouse!" << endl;
        return false;
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(!display) {
        cout << "failed to create display!" << endl;
        exit(-1);
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        cout << "failed to create timer!" << endl;
        return false;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        cout << "failed to create event_queue!" << endl;
        al_destroy_timer(timer);
        return false;
    }

    return true;
}


void deinit_allegro_devices() {
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}


void register_events_sources() {
    al_register_event_source(
        event_queue,
        al_get_display_event_source(display)
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
    Keyboard* keyboard = new Keyboard();
    GamePhase* game_phase = new GamePhase("1");
    Graphics* graphics = new Graphics();

    if(!init_allegro_devices()) {
        return -1;
    }

    register_events_sources();

    al_start_timer(timer);

    while(true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        keyboard->capture(ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            map<string, bool> keys = keyboard->read();
            list<tuple<Point2D, Point2D, Object2DType>> cur_state = game_phase->update(keys);
            graphics->draw_contour(cur_state);
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }

    delete graphics;
    delete game_phase;
    delete keyboard;

    deinit_allegro_devices();

    return 0;
}
