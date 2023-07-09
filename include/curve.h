#pragma once
#include "vec.h"

typedef struct segment_2d_s{
    vec2 p1;
    vec2 p2;
    vec2 p3;
} segment_2d;

vec2 quad_interpolate_2d(vec2 points[3], float t);
vec3 quad_interpolate_3d(vec3 points[3], float t);