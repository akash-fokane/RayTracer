#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray
{
    vec3 origin;
    vec3 direction;
} ray;

ray ray_create(vec3 point, vec3 v)
{
    ray r;
    r.origin = point;
    r.direction = v;
    return r;
}

vec3 ray_at(ray r, double t)
{
    return vec3_add(r.origin, vec3_scale(r.direction, t));
}

#endif