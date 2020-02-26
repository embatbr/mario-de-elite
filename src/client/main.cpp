/**
Client main file. Reads inputs, sends to server and show results (images and sounds).
After, sleeps for 40 milliseconds minus the processing time.
*/

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "controllers/Keyboard.h"
#include "communications/GameInputWriter.h"
#include "communications/GameOutputReader.h"
#include "../server/base/Point2D.h"
#include "../server/logic/Game.h"


#define FPS 25
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define BASE_COLOR_WHITE al_map_rgb(255, 255, 255)
#define BASE_COLOR_BLACK al_map_rgb(0, 0, 0)


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
    GameInputWriter* game_input_writer = new GameInputWriter(keyboard);
    GameOutputReader* game_output_reader = new GameOutputReader();

    Game* game = new Game();

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
            string input = game_input_writer->write();
            list<string> output_string = game->run(input);
            list<int> output = game_output_reader->read(output_string);

            int x_axis = output.front();
            output.pop_front();
            int y_axis = output.front();
            output.pop_front();
            int width = output.front();
            output.pop_front();
            int height = output.front();
            output.pop_front();

            al_clear_to_color(BASE_COLOR_BLACK);

            al_draw_filled_rectangle(
                x_axis - width/2,
                y_axis - height/2,
                x_axis + width/2,
                y_axis + height/2,
                BASE_COLOR_WHITE
            );

            al_flip_display();
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }

    deinit_allegro_devices();

    return 0;
}
