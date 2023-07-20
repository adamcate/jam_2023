#include "vec.h"
#include "collision.h"
#include "enemy_data.h"
#include "game_constants.h"
#include "mem_pool.h"
#include <libdragon.h>

#pragma once

#define MAX_PLAYER_BULLETS 40

typedef enum game_screen_e{
    GAME_STATE_MAIN_MENU,
    GAME_STATE_SETTINGS,
    GAME_STATE_STARTUP,
    GAME_STATE_IN_GAME
} game_screen;

typedef struct game_state_s{
    bool initialized;

    game_screen curr_screen;
    
    int score;
    int stage_number;
    int lives;
    int continues;

    bool paused;

    vec2 player_pos;
    vec2 player_vel;
    
    bullet player_bullets[MAX_PLAYER_BULLETS];

    MemZone enemy_bullet_pool;
    MemZone enemy_data_pool;
} game_state;

void game_state_reset(game_state *state);

void game_state_init(game_state *state);

void game_state_tick(game_state *state, SI_controllers_state_t *controller);