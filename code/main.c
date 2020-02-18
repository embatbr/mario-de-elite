#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "game/base.h"
#include "logging.h"


const float FPS = 25;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MARIO_WIDTH = 32;
const int MARIO_HEIGHT = 42;


typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_BITMAP* canvas;
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* mario_bmp;
} AllegroDevices;


int DRAW_FLAGS = 0;

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

    allegro_devices->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(!allegro_devices->display) {
        print_error("failed to create display!");
        return -1;
    }

    allegro_devices->canvas = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(!allegro_devices->canvas) {
        print_error("failed to create canvas bitmap!");
        al_destroy_display(allegro_devices->display);
        al_destroy_timer(allegro_devices->timer);
        return -1;
    }

    allegro_devices->background = al_load_bitmap("resources/images/bkg.jpg");
    if(!allegro_devices->background) {
        print_error("failed to load background");
        al_destroy_display(allegro_devices->display);
        return -1;
    }

    allegro_devices->mario_bmp = al_load_bitmap("resources/images/mario.png");
    if(!allegro_devices->mario_bmp) {
        print_error("failed to create mario_bmp bitmap!");
        al_destroy_display(allegro_devices->display);
        al_destroy_timer(allegro_devices->timer);
        return -1;
    }

    allegro_devices->event_queue = al_create_event_queue();
    if(!allegro_devices->event_queue) {
        print_error("failed to create event_queue!");
        al_destroy_display(allegro_devices->display);
        al_destroy_timer(allegro_devices->timer);
        al_destroy_bitmap(allegro_devices->canvas);
        al_destroy_bitmap(allegro_devices->background);
        al_destroy_bitmap(allegro_devices->mario_bmp);
        return -1;
    }

    return 0;
}

void deinit_allegro_devices(AllegroDevices* allegro_devices) {
    al_destroy_timer(allegro_devices->timer);
    al_destroy_display(allegro_devices->display);
    al_destroy_event_queue(allegro_devices->event_queue);
    al_destroy_bitmap(allegro_devices->canvas);
    al_destroy_bitmap(allegro_devices->background);
    al_destroy_bitmap(allegro_devices->mario_bmp);
}


void register_events_sources(AllegroDevices* allegro_devices) {
    al_register_event_source(
        allegro_devices->event_queue,
        al_get_display_event_source(allegro_devices->display)
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


void show(AllegroDevices* allegro_devices) {
    al_set_target_bitmap(al_get_backbuffer(allegro_devices->display));
    al_draw_bitmap(allegro_devices->canvas, 0, 0, 0);

    al_flip_display();
}


void draw(AllegroDevices* allegro_devices, int rgb) {
    // reset canvas
    al_set_target_bitmap(allegro_devices->canvas);
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // draw on canvas
    al_draw_bitmap(allegro_devices->background, 0, 0, 0);
    al_draw_bitmap(allegro_devices->mario_bmp, mario->physical_object->position->x_axis,
                   mario->physical_object->position->y_axis, DRAW_FLAGS);

    if(mouse_position->x_axis >= 0 && mouse_position->y_axis >= 0) {
        al_draw_filled_circle(mouse_position->x_axis, mouse_position->y_axis, 5, al_map_rgb(0, 0, 0));
        al_draw_circle(mouse_position->x_axis, mouse_position->y_axis, 15, al_map_rgb(0, 0, 0), 2);
    }

    // show on display
    show(allegro_devices);
}


void main_loop(AllegroDevices* allegro_devices) {
    bool paused = false;
    bool redraw = true;
    int rgb = 0;
    int step = 5;

    draw(allegro_devices, rgb);

    al_start_timer(allegro_devices->timer);

    while(1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(allegro_devices->event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(!paused) {
                if(mario->physical_object->position->x_axis < 0 || mario->physical_object->position->x_axis >  SCREEN_WIDTH - MARIO_WIDTH) {
                    mario->physical_object->speed->x_axis = -mario->physical_object->speed->x_axis;
                }

                if(mario->physical_object->position->y_axis < 0 || mario->physical_object->position->y_axis > SCREEN_HEIGHT - MARIO_HEIGHT) {
                    mario->physical_object->speed->y_axis = -mario->physical_object->speed->y_axis;
                }

                mario->physical_object->position->x_axis += mario->physical_object->speed->x_axis;
                mario->physical_object->position->y_axis += mario->physical_object->speed->y_axis;

                mario->physical_object->speed->x_axis = 0;
                mario->physical_object->speed->y_axis = 0;
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
                    al_save_bitmap("resources/images/canvas.bmp", allegro_devices->canvas);
                }

                paused = !paused;
            }
            else if(ev.keyboard.keycode == 59) { // ESC
                break;
            }
            else if(!paused && ev.keyboard.keycode == 1) { // LEFT
                mario->physical_object->speed->x_axis = -10;
            }
            else if(!paused && ev.keyboard.keycode == 4) { // RIGHT
                mario->physical_object->speed->x_axis = 10;
            }
            else if(!paused && ev.keyboard.keycode == 23) { // UP
                mario->physical_object->speed->y_axis = -10;
            }
            else if(!paused && ev.keyboard.keycode == 19) { // DOWN
                mario->physical_object->speed->y_axis = 10;
            }
        }
        else if(!paused && (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ||
                            ev.type == ALLEGRO_EVENT_MOUSE_AXES)) {
            mouse_position->x_axis = ev.mouse.x;
            mouse_position->y_axis = ev.mouse.y;

            if(ev.mouse.x < (mario->physical_object->position->x_axis + MARIO_WIDTH/2)) {
                DRAW_FLAGS = DRAW_FLAGS | ALLEGRO_FLIP_HORIZONTAL;
            }
            else if(DRAW_FLAGS & ALLEGRO_FLIP_HORIZONTAL == ALLEGRO_FLIP_HORIZONTAL){
                DRAW_FLAGS = DRAW_FLAGS ^ ALLEGRO_FLIP_HORIZONTAL;
            }
        }
        else if(!paused && ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) {
            mouse_position->x_axis = mouse_position->y_axis = -1;
        }
        else if(!paused && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mario->physical_object->position->x_axis = ev.mouse.x;
            mario->physical_object->position->y_axis = ev.mouse.y;
        }

        if(redraw && al_is_event_queue_empty(allegro_devices->event_queue)) {
            redraw = false;
            draw(allegro_devices, rgb);
        }

        if(!paused) {
            rgb = rgb + step;
            if(rgb == 0 || rgb == 255) {
                step = -step;
            }
        }
    }
}


void init_base() {
    mouse_position = malloc(sizeof(Point2D));
    mouse_position->x_axis = -1;
    mouse_position->y_axis = -1;

    Object2D* mario_physical_object = Object2D_init_2(100, 100, MARIO_WIDTH,
                                                      MARIO_HEIGHT, 0, 0, true);
    mario = GameObject_init(mario_physical_object);
}


int main(int argc, char** argv) {
    AllegroDevices* allegro_devices = malloc(sizeof(AllegroDevices));

    if(init_allegro_devices(allegro_devices) != 0) {
        return -1;
    }

    register_events_sources(allegro_devices);

    init_base();

    main_loop(allegro_devices);

    deinit_allegro_devices(allegro_devices);

    return 0;
}
