#ifndef COLOR_H
#define COLOR_H

#include "defines.h"
#include "interval.h"

typedef vec3 color;

void write_color(FILE *out, const color c)
{
    interval intensity = {0.000, 0.999};

    int r = (int)(255.999 * interval_clamp(intensity, c.e[0]));
    int g = (int)(255.999 * interval_clamp(intensity, c.e[1]));
    int b = (int)(255.999 * interval_clamp(intensity, c.e[2]));

    fprintf(out, "%d %d %d \n", r, g, b);
}

#endif