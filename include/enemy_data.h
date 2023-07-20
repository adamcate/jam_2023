#include "collision.h"
#include "curve.h"

#pragma once

typedef struct enemy_s enemy;

typedef enum enemy_type_e{
    ENEMY_PLACEHOLDER,
    ENEMY_SCOUT_SHIP,
    ENEMY_FIRE_TEST
} enemy_type;

typedef enum bullet_type_e{
    BULLET_WATER_ABSORB,
    BULLET_LASER,
    BULLET_PLAYER_SPAZER
} bullet_type;

typedef struct bullet_s{
    bullet_type type;
    circle_t collider;
    vec2 position;
    bool enabled;
} bullet;

typedef struct enemy_placeholder_s{
    circle_t collider;
    int health;
} enemy_placeholder;

typedef struct enemy_fire_test_data_s{
    circle_collider collider;
    int health;

    bullet *bullets;
} enemy_fire_test_data;

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