#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "physics/base.h"
#include "game/base.h"
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

Screen* screen;
GraphicObject* background;

GameScenario* scenario;

GameObject* mario;

Point2D* mouse_position;


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


void register_events_sources(AllegroDevices* allegro_devices) {
    al_register_event_source(
        allegro_devices->event_queue,
        al_get_display_event_source(screen->display)
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


void draw() {
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
    paint_screen(screen, mario->graphic_object, position->x_axis, position->y_axis, DRAW_FLAGS);

    // TODO for testing purposes only
    al_draw_filled_circle(mouse_position->x_axis, mouse_position->y_axis, 5, BASE_COLOR_BLACK);
    al_draw_circle(mouse_position->x_axis, mouse_position->y_axis, 15, BASE_COLOR_BLACK, 2);

    // show on display
    update_screen(screen);
}


void main_loop(AllegroDevices* allegro_devices) {
    bool paused = false;
    bool redraw = true;

    draw();

    al_start_timer(allegro_devices->timer);

    while(1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(allegro_devices->event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(!paused) {
                if(mario->object2d->position->x_axis < 0 || mario->object2d->position->x_axis >  SCREEN_WIDTH - MARIO_WIDTH) {
                    mario->object2d->speed->x_axis = -mario->object2d->speed->x_axis;
                }

                if(mario->object2d->position->y_axis < 0 || mario->object2d->position->y_axis > SCREEN_HEIGHT - MARIO_HEIGHT) {
                    mario->object2d->speed->y_axis = -mario->object2d->speed->y_axis;
                }

                mario->object2d->position->x_axis += mario->object2d->speed->x_axis;
                mario->object2d->position->y_axis += mario->object2d->speed->y_axis;

                mario->object2d->speed->x_axis = 0;
                mario->object2d->speed->y_axis = 0;
            }

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            // printf("%d\n", ev.keyboard.keycode);

            if(ev.keyboard.keycode == 67) { // ENTER
                if(!paused) {
                    al_save_bitmap("resources/images/canvas.bmp", screen->canvas);
                }

                paused = !paused;
            }
            else if(ev.keyboard.keycode == 59) { // ESC
                break;
            }
            else if(!paused && ev.keyboard.keycode == 1) { // LEFT
                mario->object2d->speed->x_axis = -10;
            }
            else if(!paused && ev.keyboard.keycode == 4) { // RIGHT
                mario->object2d->speed->x_axis = 10;
            }
            else if(!paused && ev.keyboard.keycode == 23) { // UP
                mario->object2d->speed->y_axis = -10;
            }
            else if(!paused && ev.keyboard.keycode == 19) { // DOWN
                mario->object2d->speed->y_axis = 10;
            }
        }
        else if(!paused && (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ||
                            ev.type == ALLEGRO_EVENT_MOUSE_AXES)) {
            mouse_position->x_axis = ev.mouse.x;
            mouse_position->y_axis = ev.mouse.y;

            if(ev.mouse.x < (mario->object2d->position->x_axis + MARIO_WIDTH/2)) {
                DRAW_FLAGS = DRAW_FLAGS | ALLEGRO_FLIP_HORIZONTAL;
            }
            else if(DRAW_FLAGS & ALLEGRO_FLIP_HORIZONTAL == ALLEGRO_FLIP_HORIZONTAL){
                DRAW_FLAGS = DRAW_FLAGS ^ ALLEGRO_FLIP_HORIZONTAL;
            }
        }
        else if(!paused && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mario->object2d->position->x_axis = ev.mouse.x;
            mario->object2d->position->y_axis = ev.mouse.y;
        }

        if(redraw && al_is_event_queue_empty(allegro_devices->event_queue)) {
            redraw = false;
            draw();
        }
    }
}


void init_base() {
    mouse_position = malloc(sizeof(Point2D));
    mouse_position->x_axis = -1;
    mouse_position->y_axis = -1;

    screen = Screen_init(SCREEN_WIDTH, SCREEN_HEIGHT);

    background = GraphicObject_init("backgrounds/05.png");

    scenario = GameScenario_init(NUM_BLOCKS);

    Object2D* mario_object2d = Object2D_init_2(100, 100, MARIO_WIDTH, MARIO_HEIGHT, 0, 0, true);
    mario = GameObject_init(mario_object2d, "mario.png");
}


int main(int argc, char** argv) {
    AllegroDevices* allegro_devices = malloc(sizeof(AllegroDevices));

    if(init_allegro_devices(allegro_devices) != 0) {
        return -1;
    }

    init_base();
    register_events_sources(allegro_devices);

    main_loop(allegro_devices);

    deinit_allegro_devices(allegro_devices);

    return 0;
}
