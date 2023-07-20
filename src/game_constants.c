#include "../include/game_constants.h"
#include "../include/game.h"

#define KILOBYTES(x) x * 1024

const int screen_width = 320;
const int screen_height = 240;

const float player_mov_vel = 2.5f;

const vec2 player_initial_pos = {.x = 160, .y = 30};
const int initial_lives = 5;
const int num_continues = 2;

const int max_player_bullets = 30;
const float player_hitbox_radius = 12.5f;

const size_t enemy_bullet_pool_size = KILOBYTES(8);
const size_t enemy_data_pool_size = KILOBYTES(32);

const game_state game_state_default = {.initialized = false};