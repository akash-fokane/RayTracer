#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray
{
    vec3 orig;
    vec3 dir;
} ray;

ray ray_create(vec3 point, vec3 v)
{
    ray r;
    r.orig = point;
    r.dir = v;
    return r;
}

vec3 ray_at(ray r, double t)
{
    return vec3_add(r.orig, vec3_scale(r.dir, t));
}

#endif