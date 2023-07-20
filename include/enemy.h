#pragma once
#include "collision.h"
#include "vec.h"
#include "curve.h"
#include "enemy_data.h"
#include "game.h"

typedef struct enemy_s{
    enemy_type type;
    bool enabled;

    vec2 root_position;

    int frame_timer;
    
    union{
        enemy_placeholder placeholder_data;
        enemy_turret_data turret_data;
        enemy_boss_data boss_data;
    } enemy_data;
}enemy;

void update_enemy(enemy *instance, game_state *state);
void add_enemy(enemy *instance, enemy_type type, game_state *state);
void disable_enemy(enemy *instance, game_state *state);