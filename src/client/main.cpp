/**
Client main file. Reads inputs, sends to server and show results (images and sounds).
After, sleeps for 40 milliseconds minus the processing time.
*/

#include <allegro5/allegro.h>
#include <iostream>
#include <map>
using namespace std;

#include "controllers/Keyboard.h"


#define FPS 25


ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_TIMER* timer = NULL;


bool init_allegro_devices() {
    if(!al_init()) {
        cout << "failed to initialize allegro!" << endl;
        return false;
    }

    if(!al_install_keyboard()) {
        cout << "failed to initialize the keyboard!" << endl;
        return -1;
    }

    if(!al_install_mouse()) {
        cout << "failed to initialize the mouse!" << endl;
        return -1;
    }

    display = al_create_display(640, 480);
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
            map<int, bool> keys = keyboard->read();

            cout << "key_pause_pressed: " << keys[KEY_PAUSE] << endl;
            cout << "key_select_pressed: " << keys[KEY_SELECT] << endl;
            cout << "key_left_pressed: " << keys[KEY_LEFT] << endl;
            cout << "key_right_pressed: " << keys[KEY_RIGHT] << endl;
            cout << "key_up_pressed: " << keys[KEY_UP] << endl;
            cout << "key_down_pressed: " << keys[KEY_DOWN] << endl << endl;
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }

    deinit_allegro_devices();

    return 0;
}
