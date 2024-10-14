#ifndef BALL_H_
#define BALL_H_

#include "playground.h"

typedef struct
{
    float radius, mass;

    // center of the ball
    Vector2D location;
    Vector2D velocity;
} Ball;

void ball_move(Ball *ball, float dt, float deceleration);

void ball_collision_adjust_velocity(Ball *ball1, Ball *ball2, float distance);

void ball_collision_adjust_positions(Ball *ball1, Ball *ball2, float distance);

void ball_adjust_small_velocity(Ball *ball);

#endif
