#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct vec3
{
    double e[3];
} vec3;

typedef vec3 point3;

static inline vec3 vec3_create(double e0, double e1, double e2)
{
    vec3 v = {{e0, e1, e2}};
    return v;
}

static inline vec3 vec3_negate(const vec3 *v)
{
    return vec3_create(-v->e[0], -v->e[1], -v->e[2]);
}

static inline vec3 vec3_add(const vec3 *v, const vec3 *u)
{
    return vec3_create(v->e[0] + u->e[0], v->e[1] + u->e[1], v->e[2] + u->e[2]);
}

static inline vec3 vec3_sub(const vec3 *v, const vec3 *u)
{
    return vec3_create(v->e[0] - u->e[0], v->e[1] - u->e[1], v->e[2] - u->e[2]);
}

static inline vec3 vec3_mul(const vec3 *v, const vec3 *u)
{
    return vec3_create(v->e[0] * u->e[0], v->e[1] * u->e[1], v->e[2] * u->e[2]);
}

static inline vec3 vec3_scale(const vec3 *v, double c)
{
    return vec3_create(c * v->e[0], c * v->e[1], c * v->e[2]);
}

static inline vec3 vec3_div(const vec3 *v, double c)
{
    return vec3_scale(v, 1.0 / c);
}

static inline double vec3_dot(const vec3 *v, const vec3 *u)
{
    return (v->e[0] * u->e[0] + v->e[1] * u->e[1] + v->e[2] * u->e[2]);
}

static inline vec3 vec3_cross(const vec3 *v, const vec3 *u)
{
    return vec3_create(
        v->e[1] * u->e[2] - v->e[2] * u->e[1],
        v->e[2] * u->e[0] - v->e[0] * u->e[2],
        v->e[0] * u->e[1] - v->e[1] * u->e[0]);
}

static inline double vec3_length_squared(const vec3 *v)
{
    return vec3_dot(v, v);
}

static inline double vec3_length(const vec3 *v)
{
    return sqrt(vec3_dot(v, v));
}

static inline vec3 vec3_unit(const vec3 *v)
{
    return vec3_div(v, vec3_length(v));
}

static inline int vec3_near_zero(const vec3 *v)
{
    const double s = 1e-8;
    return fabs(v->e[0]) < s && fabs(v->e[1]) < s && fabs(v->e[2]) < s;
}

static inline void vec3_print(const vec3 *v)
{
    printf("%f %f %f \n", v->e[0], v->e[1], v->e[2]);
}

#endif