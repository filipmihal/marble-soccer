#include <math.h>

#include "playground.h"

Vector2D compute_unit_vector(Vector2D vector)
{
    float magnitude = sqrtf(powf(vector.x, 2) + powf(vector.y, 2));

    if (magnitude == 0.0f)
        return (Vector2D){0, 0};

    return (Vector2D){vector.x / magnitude, vector.y / magnitude};
}