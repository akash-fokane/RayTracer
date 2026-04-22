#ifndef SPHERE_H
#define SPHERE_H

#include "interval.h"

typedef struct sphere sphere;

typedef bool (*fptr_hit)(sphere *self, ray r, interval ray_t);

typedef struct
{
    vec3 p;
    vec3 normal;
    double t;
    bool front_face;
} hit_record;

typedef struct sphere
{
    double radius;
    vec3 center;
    hit_record record;
    fptr_hit hit;
} sphere;

bool sphere_hit(sphere *self, ray r, interval ray_t)
{
    vec3 oc = vec3_sub(self->center, r.origin);
    double a = vec3_dot(r.direction, r.direction);
    double h = vec3_dot(r.direction, oc);
    double c = vec3_dot(oc, oc) - self->radius * self->radius;
    double discriminant = h * h - a * c;
    if (discriminant < 0)
    {
        return false;
    }

    double sqrtd = sqrt(discriminant);

    double root = (h - sqrtd) / a;
    if (!interval_surrounds(ray_t, root))
    {
        root = (h + sqrtd) / a;
        if (!interval_surrounds(ray_t, root))
            return false;
    }

    self->record.t = root;
    self->record.p = ray_at(r, self->record.t);
    self->record.normal = vec3_div(vec3_sub(self->record.p, self->center), self->radius);

    self->record.front_face = (vec3_dot(r.direction, self->record.normal) < 0);
    self->record.normal = self->record.front_face ? self->record.normal : vec3_negate(self->record.normal);

    return true;
}

#endif