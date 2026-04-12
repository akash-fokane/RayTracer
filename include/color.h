#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

typedef vec3 color;

void write_color(FILE *out, const color *c){
    int r = (int)(255.999 * c->e[0]);
    int g = (int)(255.999 * c->e[1]);
    int b = (int)(255.999 * c->e[2]);

    fprintf(out, "%d %d %d \n",r , g ,b);
}

#endif