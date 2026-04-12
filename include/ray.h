#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray
{
    point3 orig;
    vec3 dir;
} ray;

ray ray_create(const point3 *point, const vec3 *v){
    ray r;
    r.orig = *point;
    r.dir = *v;
    return r;
}

point3 ray_at(const ray *r, double t){
    vec3 scaled = vec3_scale(&r->dir,t);
    return vec3_add(&r->orig,&scaled);
}

#endif