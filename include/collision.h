#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "vec.h"


typedef enum collision_type_e{
    COLL_TRIGGER,
    COLL_DAMAGE,
    COLL_WEAKPOINT,
    COLL_PUSH
} collision_type_t;

typedef struct circle_s {
	float x, y;
	float r;
} circle_t;

typedef struct circle_collider_s {
    bool enabled;
    circle_t circle;
    collision_type_t type;
    int health;
} circle_collider;

bool circle_overlaps(circle_t c1, circle_t c2);