#ifndef INTERVAL_H
#define INTERVAL_H

#include "defines.h"

typedef struct 
{
    double min;
    double max;
}interval;

static inline bool interval_contains(interval i, double t)
{
    return (t>=i.min && t<=i.max);
}

static inline bool interval_surrounds(interval i, double t)
{
    return (t>i.min && t<i.max);
}

static const interval INTERVAL_EMPTY = {.min = +infinity, .max = -infinity};
static const interval INTERVAL_UNIVERSE = {.min = -infinity, .max = +infinity};

#endif