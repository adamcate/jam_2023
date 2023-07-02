#include "../include/curve.h"

vec2 quad_interpolate_2d(vec2 points[3], float t){
    if(t < 0.f) t = 0.f;
    if(t > 1.f) t = 1.f;

    vec2 result = vec2_add(vec2_add(vec2_mult_coeff(points[0],(1-t)*(1-t)),vec2_mult_coeff(points[1],2*(1-t)*t)),
    vec2_mult_coeff(points[2],t*t));

    return result;
}

vec3 quad_interpolate_3d(vec3 points[3], float t){
    if(t < 0.f) t = 0.f;
    if(t > 1.f) t = 1.f;

    vec3 result = vec3_add(vec3_add(vec3_mult_coeff(points[0],(1-t)*(1-t)),vec3_mult_coeff(points[1],2*(1-t)*t)),
    vec3_mult_coeff(points[2],t*t));

    return result;
}