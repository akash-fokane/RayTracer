#include <stdio.h>
#include <stdint.h>

#include "main.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

color ray_color(const ray *r)
{
    return (color){{0, 0, 0}};
}

int main()
{
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // image height calculation
    int image_height = (int)(image_height / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // camera
    double focal_length = 1.0;
    int viewport_height = 2.0;
    int viewport_width = viewport_height * ((double)(image_width / image_height));
    point3 camera_center = (point3){{0, 0, 0}};

    vec3 viewport_u = vec3_create(viewport_width, 0, 0);
    vec3 viewport_v = vec3_create(0, -viewport_height, 0);

    uint16_t image_width = IMAGE_WIDTH,
             image_height = IMAGE_HEIGHT;
    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int i = 0; i < image_height; i++)
    {
        fprintf(stderr, "\rLines Remaining:%d   ", image_height - i);
        fflush(stderr);

        for (int j = 0; j < image_width; j++)
        {
            color c = vec3_create(j * 1.0f / (image_width - 1), i * 1.0f / (image_height - 1), 0);
            write_color(stdout, &c);
        }
    }

    fprintf(stderr, "!Done\n");

    // return 0;
}