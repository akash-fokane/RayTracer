#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "defines.h"
#include "sphere.h"
#include "hittable.h"

int main()
{
    hittables_list world = {0};
    sphere s1 = {.center = {0, 0, -1}, .hit = sphere_hit, .radius = 0.5, .record = {0}};
    hittable_add(&world, &s1);
    sphere s2 = {.center = {0, -100.5, -1}, .hit = sphere_hit, .radius = 100, .record = {0}};
    hittable_add(&world, &s2);

    camera cam = {.aspect_ratio = 16.0 / 9.0, .image_width = 800};

    camera_render(&cam, &world);

    return 0;
}