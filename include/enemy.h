#pragma once
#include "collision.h"
#include "vec.h"
#include "curve.h"
#include "enemy_data.h"

typedef struct enemy_s{
    enemy_type type;
    bool enabled;

    vec2 root_position;

    union{
        enemy_placeholder placeholder_data;
        enemy_turret_data turret_data;
        enemy_boss_data boss_data;
    } enemy_data;
}enemy;