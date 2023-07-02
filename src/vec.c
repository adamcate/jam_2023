#include "../include/vec.h"

vec2 vec2_proj(vec2 v1, vec2 v2){
    vec2 result = {0.f,0.f};
    
    float mag_v2_squared = v2.x * v2.x + v2.y * v2.y;

    if (mag_v2_squared == 0.f) return result;

    float mag_proj = vec2_mult_dot(v1,v2) / mag_v2_squared;

    return (vec2_mult_coeff(v1,mag_proj));
}

vec3 vec3_proj(vec3 v1, vec3 v2){
    vec3 result = {0.f,0.f,0.f};
    
    float mag_v2_squared = v2.x * v2.x + v2.y * v2.y + v2.z * v2.z;

    if (mag_v2_squared == 0.f) return result;

    float mag_proj = vec3_mult_dot(v1,v2) / mag_v2_squared;

    return (vec3_mult_coeff(v1,mag_proj));
}