#pragma once

typedef struct{
    float x, y;
} vec2;

typedef struct{
    float x, y, z;
} vec3;

inline vec2 vec2_add(vec2 v1, vec2 v2){
    vec2 result = {v1.x + v2.x, v1.y + v2.y};
    return result;
}

inline vec3 vec3_add(vec3 v1, vec3 v2){
    vec3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return result;
}

inline vec2 vec2_sub(vec2 v1, vec2 v2){
    vec2 result = {v1.x - v2.x, v1.y - v2.y};
    return result;
}

inline vec3 vec3_sub(vec3 v1, vec3 v2){
    vec3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}

inline float vec2_mult_dot(vec2 v1, vec2 v2){
    float result = v1.x * v2.x + v1.y * v2.y;
    return result;
}

inline float vec3_mult_dot(vec3 v1, vec3 v2){
    float result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return result;
}

inline vec2 vec2_mult_coeff(vec2 v1, float scalar){
    vec2 result = {v1.x * scalar, v1.y * scalar};
    return result;
}

inline vec3 vec3_mult_coeff(vec3 v1, float scalar){
    vec3 result = {v1.x * scalar, v1.y * scalar, v1.z * scalar};
    return result;
}

inline vec3 vec3_mult_cross(vec3 v1, vec3 v2){
    vec3 result = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.z};
    return result;
}

inline vec2 vec2_proj(vec2 v1, vec2 v2){
    vec3 result = {};
}