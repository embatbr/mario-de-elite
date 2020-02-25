/**
Client main file. Reads inputs, sends to server and show results (images and sounds).
After, sleeps for 40 milliseconds minus the processing time.
*/

#include <iostream>
#include <map>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "controllers/Keyboard.h"
#include "../server/base/Point2D.h"


#define FPS 25
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SPEED 5

#define BASE_COLOR_WHITE al_map_rgb(255, 255, 255)
#define BASE_COLOR_BLACK al_map_rgb(0, 0, 0)
#define SIZE 20


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

    Point2D *player = new Point2D(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    int x_speed = 0;
    int y_speed = 0;

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

            if(keys[KEY_PAUSE]) {
                break;
            }
            if(keys[KEY_LEFT]) {
                x_speed = x_speed - SPEED;
            }
            if(keys[KEY_RIGHT]) {
                x_speed = x_speed + SPEED;
            }
            if(keys[KEY_UP]) {
                y_speed = y_speed - SPEED;
            }
            if(keys[KEY_DOWN]) {
                y_speed = y_speed + SPEED;
            }

            player->move(x_speed, y_speed);

            cout << "x_speed: " << x_speed << endl;
            cout << "y_speed: " << y_speed << endl;
            cout << "x_axis: " << player->x_axis << endl;
            cout << "y_axis: " << player->y_axis << endl;

            al_clear_to_color(BASE_COLOR_BLACK);

            // drawing happens here
            al_draw_filled_rectangle(
                player->x_axis - SIZE/2,
                player->y_axis - SIZE/2,
                player->x_axis + SIZE/2,
                player->y_axis + SIZE/2,
                BASE_COLOR_WHITE
            );

            al_flip_display();

            x_speed = 0;
            y_speed = 0;
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }

    deinit_allegro_devices();

    return 0;
}
