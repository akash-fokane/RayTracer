#ifndef DEFINES_H
#define DEFINES_H

#include <float.h>
#include <time.h>
#include <stdlib.h>

static const double infinity = FLT_MAX;
static const double pi = 3.1415926535897932385;

static inline double degree_to_radian(double degrees)
{
    return (degrees * pi) / 180.0;
}

static inline double random_double(double min, double max)
{
    double rand_unit = rand() / (RAND_MAX + 1.0);
    return min + (max - min) * rand_unit;
}

#include "vec3.h"
#include "ray.h"
#include "interval.h"
#include "hittable.h"
#include "color.h"
#include "camera.h"

#endif