#include <stdlib.h>
#include "vec.h"

#pragma once

typedef struct game_state_s game_state;

extern const int screen_width;
extern const int screen_height;

extern const float player_mov_vel;

extern const vec2 player_initial_pos;
extern const int initial_lives;
extern const int num_continues;

extern const int max_player_bullets;
extern const float player_hitbox_radius;

extern const size_t enemy_bullet_pool_size;
extern const size_t enemy_data_pool_size;

extern const game_state game_state_default;