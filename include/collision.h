#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "vec.h"


typedef enum collision_type_e collision_type_t;

typedef struct circle_s {
	float x, y;
	float r;
} circle_t;

typedef struct collider_s {
    circle_t circle;
    collision_type_t type;
} collider_t;

typedef struct enemy_s{
    collider_t *colliders;
    int health;
    // TODO: add bezier interpolated path information
    vec3 path[3];
} enemy_t;

typedef enum collision_type_e{
    COLL_TRIGGER,
    COLL_DAMAGE,
    COLL_WEAKPOINT,
    COLL_PUSH
} collision_type_t;

bool circle_overlaps(circle_t *c1, circle_t *c2);