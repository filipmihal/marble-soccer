#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "playground.h"
#include "ball.h"
#include "simulation.h"

static void handle_wall_collisions(Ball *balls[], Playground *playground, int num_balls)
{
    for (int i = 0; i < num_balls; i++)
    {
        if (balls[i]->location.x - balls[i]->radius < 0)
        {
            balls[i]->location.x = balls[i]->radius;
            balls[i]->velocity.x = fabsf(balls[i]->velocity.x);
        }
        else if (balls[i]->location.x + balls[i]->radius > playground->width)
        {
            balls[i]->location.x = playground->width - balls[i]->radius;
            balls[i]->velocity.x = -fabsf(balls[i]->velocity.x);
        }

        if (balls[i]->location.y - balls[i]->radius < 0)
        {
            balls[i]->location.y = balls[i]->radius;
            balls[i]->velocity.y = fabsf(balls[i]->velocity.y);
        }
        else if (balls[i]->location.y + balls[i]->radius > playground->height)
        {
            balls[i]->location.y = playground->height - balls[i]->radius;
            balls[i]->velocity.y = -fabsf(balls[i]->velocity.y);
        }
    }
}

static void handle_ball_collisions(Ball *balls[], int num_balls)
{
    for (int i = 0; i < num_balls; i++)
    {
        for (int j = i + 1; j < num_balls; j++)
        {
            float distance = sqrtf(powf(balls[i]->location.x - balls[j]->location.x, 2) + powf(balls[i]->location.y - balls[j]->location.y, 2));
            if (distance <= balls[i]->radius + balls[j]->radius)
            {
                ball_collision_adjust_positions(balls[i], balls[j], distance);
                ball_collision_adjust_velocity(balls[i], balls[j], balls[i]->radius + balls[j]->radius);
            }
        }
    }
}

void simulate(Ball *balls[], Playground *playground, int num_balls, float dt)
{

    handle_wall_collisions(balls, playground, num_balls);
    handle_ball_collisions(balls, num_balls);

    for (int i = 0; i < num_balls; i++)
    {
        ball_move(balls[i], dt, playground->deceleration);
        ball_adjust_small_velocity(balls[i]);
    }
}

bool is_simulation_idle(Ball *balls[], int num_balls)
{
    for (int i = 0; i < num_balls; i++)
    {
        if (balls[i]->velocity.x != 0 || balls[i]->velocity.y != 0)
        {
            return false;
        }
    }
    return true;
}