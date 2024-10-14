#ifndef PLAYGROUND_H_
#define PLAYGROUND_H_

#include "constants.h"

// Top-left location
typedef struct
{
    float x, y;
} Vector2D;

typedef struct
{
    int width, height, net_size;
    float deceleration;
} Playground;

Vector2D compute_unit_vector(Vector2D vector);

#endif
