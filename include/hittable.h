#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "ray.h"
#include "sphere.h"

#define MAX_HITTABLES 100

typedef struct
{
    sphere *hittables[MAX_HITTABLES];
    int count;
    hit_record record;
} hittables_list;

void hittable_add(hittables_list *l, sphere *s)
{
    if (l->count < MAX_HITTABLES)
    {
        l->hittables[l->count++] = s;
    }
}

bool hittables_list_hit(hittables_list *l, ray r, interval ray_t)
{
    bool hit_anything = false;
    double closest = ray_t.max;

    for (int i = 0; i < l->count; i++)
    {
        sphere *s = l->hittables[i];
        if (s->hit(s, r, (interval){ray_t.min, closest}))
        {
            hit_anything = true;
            closest = s->record.t;
            l->record = s->record;
        }
    }

    return hit_anything;
}

#endif