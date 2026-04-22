#ifndef CAMERA_H
#define CAMERA_H

#include "defines.h"

typedef struct
{
    double aspect_ratio;
    int image_width;

    int image_height;
    vec3 center;
    vec3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
}camera;

void camera_init(camera *cam)
{
    cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
    cam->image_height = (cam->image_height < 1) ? 1 : cam->image_height;

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * cam->aspect_ratio;
    cam->center = (vec3){{0, 0, 0}};

    vec3 viewport_u = vec3_create(viewport_width, 0, 0);
    vec3 viewport_v = vec3_create(0, -viewport_height, 0);

    cam->pixel_delta_u = vec3_div(viewport_u, cam->image_width);
    cam->pixel_delta_v = vec3_div(viewport_v, cam->image_height);

    vec3 viewport_upper_left = vec3_sub(
        vec3_sub(cam->center, vec3_create(0, 0, focal_length)),
        vec3_scale(vec3_add(viewport_u, viewport_v), 0.5));


    cam->pixel00_loc = vec3_add(viewport_upper_left, vec3_div(vec3_add(cam->pixel_delta_u, cam->pixel_delta_v), 2));
}

color camera_ray_color(camera *cam, ray r, hittables_list *world)
{
    if (hittables_list_hit(world, r, (interval){0, infinity}))
    {
        vec3 N = world->record.normal;
        return vec3_scale(vec3_offset(N, 1.0, 1.0, 1.0), 0.5);
    }

    vec3 unit_direction = vec3_unit(r.direction);
    double a = 0.5 * (unit_direction.e[1] + 1);
    return vec3_add(
        vec3_scale(vec3_create(1.0, 1.0, 1.0), 1.0 - a),
        vec3_scale(vec3_create(0.5, 0.7, 1.0), a));
}

void camera_render(camera *cam, hittables_list *world)
{
    camera_init(cam);

    printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);

    for (int i = 0; i < cam->image_height; i++)
    {
        fprintf(stderr, "\rLines Remaining:%d   ", cam->image_height - i - 1);
        fflush(stderr);

        for (int j = 0; j < cam->image_width; j++)
        {
            vec3 pixel_center = vec3_add(cam->pixel00_loc, vec3_add(vec3_scale(cam->pixel_delta_u, j), vec3_scale(cam->pixel_delta_v, i)));
            vec3 ray_direction = vec3_sub(pixel_center, cam->center);

            ray r = ray_create(cam->center, ray_direction);
            color pixel_color = camera_ray_color(cam, r, world);
            write_color(stdout, &pixel_color);
        }
    }
    fprintf(stderr, "\r!Done              \n");
}

#endif