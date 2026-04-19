#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

double hit_sphere(vec3 center, double radius, ray r)
{
    vec3 oc = vec3_sub(center, r.origin);
    double a = vec3_dot(r.direction, r.direction);
    double h = vec3_dot(r.direction, oc);
    double c = vec3_dot(oc, oc) - radius * radius;
    double discriminant = h * h - a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (h - sqrt(discriminant)) / a;
    }
}

color ray_color(ray r)
{
    double t = hit_sphere(vec3_create(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = vec3_unit(vec3_sub(ray_at(r, t), vec3_create(0, 0, -1)));
        return vec3_scale(vec3_offset(N, 1.0, 1.0, 1.0), 0.5);
    }

    vec3 unit_direction = vec3_unit(r.direction);
    double a = 0.5 * (unit_direction.e[1] + 1);
    return vec3_add(
        vec3_scale(vec3_create(1.0, 1.0, 1.0), 1.0 - a),
        vec3_scale(vec3_create(0.5, 0.7, 1.0), a));
}

int main()
{
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // image height calculation
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * aspect_ratio;
    vec3 camera_center = (vec3){{0, 0, 0}};

    vec3 viewport_u = vec3_create(viewport_width, 0, 0);
    vec3 viewport_v = vec3_create(0, -viewport_height, 0);

    vec3 pixel_delta_u = vec3_div(viewport_u, image_width);
    vec3 pixel_delta_v = vec3_div(viewport_v, image_height);

    vec3 focal_dist = vec3_create(0, 0, focal_length);
    vec3 half_u = vec3_div(viewport_u, 2);
    vec3 half_v = vec3_div(viewport_v, 2);
    vec3 viewport_upper_left = vec3_sub(camera_center, focal_dist);
    viewport_upper_left = vec3_sub(viewport_upper_left, vec3_add(half_u, half_v));

    vec3 pixel00_loc = vec3_add(viewport_upper_left, vec3_div(vec3_add(pixel_delta_u, pixel_delta_v), 2));

    // uint16_t image_width = IMAGE_WIDTH,
    //          image_height = IMAGE_HEIGHT;
    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int i = 0; i < image_height; i++)
    {
        fprintf(stderr, "\rLines Remaining:%d   ", image_height - i);
        fflush(stderr);

        for (int j = 0; j < image_width; j++)
        {
            vec3 pixel_center = vec3_add(pixel00_loc, vec3_add(vec3_scale(pixel_delta_u, j), vec3_scale(pixel_delta_v, i)));
            vec3 ray_direction = vec3_sub(pixel_center, camera_center);

            ray r = ray_create(camera_center, ray_direction);
            color pixel_color = ray_color(r);

            // color c = vec3_create(j * 1.0f / (image_width - 1), i * 1.0f / (image_height - 1), 0);
            write_color(stdout, &pixel_color);
        }
    }

    fprintf(stderr, "!Done\n");

    // return 0;
}