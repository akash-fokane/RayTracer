#include <stdio.h>
#include <stdint.h>

#include "../include/main.h"

int main()
{
    uint16_t image_width = IMAGE_WIDTH, image_height = IMAGE_HEIGHT;
    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int i = 0; i < image_height; i++)
    {
        fprintf(stderr, "\rLines Remaining:%d   ", image_height - i);
        fflush(stderr);

        for (int j = 0; j < image_width; j++)
        {
            float r = j * 1.0f / (image_width - 1);
            float g = i * 1.0f / (image_height - 1);
            float b = 0;

            int ir = (int)(r * 255.999);
            int ig = (int)(g * 255.999);
            int ib = (int)(b * 255.999);

            printf("%d %d %d \n", ir, ig, ib);
        }
    }

    fprintf(stderr, "!Done\n");

    // return 0;
}