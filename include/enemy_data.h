#include "collision.h"
#include "curve.h"

#pragma once

typedef struct enemy_s enemy;

typedef enum enemy_type_e{
    ENEMY_PLACEHOLDER,
    ENEMY_SCOUT_SHIP
} enemy_type;

typedef enum bullet_type_e{
    BULLET_WATER_ABSORB,
    BULLET_LASER
} bullet_type;

typedef struct enemy_placeholder_s{
    circle_t collider;
    int health;
} enemy_placeholder;

typedef struct enemy_turret_data_s{
    float angle;
    int health;

    bullet_type projectile_type;
    float rot_speed;

    float spread_angle;
    float fire_rate;

    int spread_amount;
            
    enemy *root_enemay;

    circle_collider collider;
} enemy_turret_data;
        
typedef struct enemy_boss_data_s{
    int num_phases;
    int curr_phase;
    int tot_health;

    circle_collider *colliders;
    segment_2d **paths;
    int curr_path_seg_index;
} enemy_boss_data;