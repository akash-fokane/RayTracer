#ifndef DEFINES_H
#define DEFINES_H

#include <float.h>

const double infinity  = FLT_MAX;
const double pi = 3.1415926535897932385;

inline double degree_to_radian(double degrees)
{
    return (degrees*pi)/180.0;
}

#include "vec3.h"
#include "color.h"
#include "ray.h"

#endif