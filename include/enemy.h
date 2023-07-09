#pragma once
#include "collision.h"
#include "vec.h"
#include "curve.h"

typedef enum enemy_type_e{
    ENEMY_SCOUT_SHIP
} enemy_type;

typedef enum bullet_type_e{
    BULLET_WATER_ABSORB,
    BULLET_LASER
} bullet_type;

typedef struct enemy_s{
    enemy_type type;
    bool enabled;

    vec2 root_position;

    union enemy_data{
        struct turret_data{
            float angle;
            int health;

            bullet_type projectile;
            bullet_type rot_speed;

            float spread_angle;
            float fire_rate;

            int spread_amount;
            
            enemy *root_enemy;

            circle_collider collider;
        };
        struct boss_data{
            int num_phases;
            int curr_phase;
            int tot_health;

            circle_collider *colliders;
            segment_2d **paths;
            int *curr_path_seg_index;
        };
    };
}enemy;