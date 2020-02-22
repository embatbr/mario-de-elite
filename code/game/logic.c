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


// for tests only
void draw_game_object(GameObject* game_object) {
    Point2D* position = game_object->object2d->position;
    Box2D* box = game_object->object2d->box;

    int x_left_sup = position->x_axis - box->width/2;
    int y_left_sup = position->y_axis - box->height/2;
    int x_right_inf = position->x_axis + box->width/2;
    int y_right_inf = position->y_axis + box->height/2;

    ALLEGRO_COLOR color;
    if(game_object->type == GAME_OBJECT_SPRITED) {
        color = BASE_COLOR_BLACK;
    }
    else if(game_object->type == GAME_OBJECT_PLATFORM) {
        color = BASE_COLOR_RED;
    }
    else if(game_object->type == GAME_OBJECT_BLOCK) {
        color = BASE_COLOR_BLUE;
    }
    al_draw_rectangle(x_left_sup, y_left_sup, x_right_inf, y_right_inf, color, 1);
}

void draw_sprited_game_object(Screen* screen, SpritedGameObject* sprited_game_object) {
    GameObject* game_object = sprited_game_object->game_object;
    Point2D* position = game_object->object2d->position;
    Box2D* box = game_object->object2d->box;

    int x_left_sup = position->x_axis - box->width/2;
    int y_left_sup = position->y_axis - box->height/2;

    paint_screen(screen, sprited_game_object->graphic_object, x_left_sup, y_left_sup,
        sprited_game_object->graphic_object->flags);
    draw_game_object(game_object); // for tests only
}

void draw_game_play(GamePlay* game_play) {
    Screen* screen = game_play->screen;
    GraphicObject* background = game_play->background;
    GameScenario* scenario = game_play->scenario;
    SpritedGameObject* mario = game_play->mario;
    Point2D* mouse_position = game_play->controllers->mouse->position;

    // reset canvas
    clear_screen(screen);

    // draw on canvas
    paint_screen(screen, background, 0, 0, 0);

    // for tests only
    for(int i = 0; i < scenario->num_game_objects; i++) {
        GameObject* game_object = *(scenario->game_objects + i);
        draw_game_object(game_object);
    }

    draw_sprited_game_object(screen, mario);

    // for tests only
    al_draw_filled_circle(mouse_position->x_axis, mouse_position->y_axis, 5, BASE_COLOR_BLACK);
    al_draw_circle(mouse_position->x_axis, mouse_position->y_axis, 15, BASE_COLOR_BLACK, 2);

    // show on display
    update_screen(screen);
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
        Controllers_init(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
    );
}


void main_loop(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* event_queue, GamePlay* game_play) {
    Screen* screen = game_play->screen;
    SpritedGameObject* mario = game_play->mario;
    Keyboard* keyboard = game_play->controllers->keyboard;
    Mouse* mouse = game_play->controllers->mouse;

    Point2D* mario_position = game_play->mario->game_object->object2d->position;
    Box2D* mario_box = game_play->mario->game_object->object2d->box;
    Speed2D* mario_speed = game_play->mario->game_object->object2d->speed;
    mario_speed->x_axis = mario_speed->y_axis = 0;

    draw_game_play(game_play);
    al_start_timer(timer);

    game_play->state = RUNNING;

    while(game_play->state != TERMINATED) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(keyboard->key_pause_pressed) {
                game_play->state = TERMINATED;
            }

            mario_speed->x_axis = MARIO_X_SPEED * direction_h(keyboard);
            mario_speed->y_axis = MARIO_Y_SPEED * direction_v(keyboard);

            mario_position->x_axis += mario_speed->x_axis;
            mario_position->y_axis += mario_speed->y_axis;

            // direction to where mario is looking (L or R)
            if(mouse->inside_display && mouse->position->x_axis < mario_position->x_axis) {
                mario->graphic_object->flags = mario->graphic_object->flags | ALLEGRO_FLIP_HORIZONTAL;
            }
            else if(mouse->inside_display && mario->graphic_object->flags & ALLEGRO_FLIP_HORIZONTAL == ALLEGRO_FLIP_HORIZONTAL){
                mario->graphic_object->flags = mario->graphic_object->flags ^ ALLEGRO_FLIP_HORIZONTAL;
            }

            // for tests only
            if(mouse->inside_display && mouse->button_right_pressed) {
                mario_position->x_axis = mouse->position->x_axis;
                mario_position->y_axis = mouse->position->y_axis;
            }

            // checks horizontal limits
            if(mario_position->x_axis < mario_box->width/2) {
                mario_position->x_axis = mario_box->width/2;
            }
            else if(mario_position->x_axis > screen->width - mario_box->width/2) {
                mario_position->x_axis = screen->width - mario_box->width/2;
            }

            // checks vertical limits
            if(mario_position->y_axis < mario_box->height/2) {
                mario_position->y_axis = mario_box->height/2;
            }
            else if(mario_position->y_axis > screen->height - mario_box->height/2) {
                mario_position->y_axis = screen->height - mario_box->height/2;
            }

            mario_speed->x_axis = 0;
            mario_speed->y_axis = 0;

            draw_game_play(game_play); // updates canvas even when paused
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            game_play->state = TERMINATED;
        }

        capture_keyboard_event(ev, keyboard);
        capture_mouse_event(ev, mouse);
    }
}
