#include <math.h>

#include "ball.h"
#include "playground.h"
#include "constants.h"

static Vector2D ball_compute_position(Ball *ball, float dt, float deceleration)
{
    float speed = sqrtf(powf(ball->velocity.x, 2) + powf(ball->velocity.y, 2));

    Vector2D unit_vector = compute_unit_vector(ball->velocity);

    float distance = speed * dt - 0.5 * deceleration * powf(dt, 2);

    float dx = unit_vector.x * distance;
    float dy = unit_vector.y * distance;

    return (Vector2D){ball->location.x + dx, ball->location.y + dy};
}

static Vector2D ball_compute_velocity(Ball *ball, float dt, float deceleration)
{

    float speed = sqrtf(powf(ball->velocity.x, 2) + powf(ball->velocity.y, 2));

    Vector2D unit_vector = compute_unit_vector(ball->velocity);

    float new_speed = speed - deceleration * dt;

    return (Vector2D){new_speed * unit_vector.x, new_speed * unit_vector.y};
}

void ball_move(Ball *ball, float dt, float deceleration)
{
    float speed = sqrtf(powf(ball->velocity.x, 2) + powf(ball->velocity.y, 2));

    float max_time = speed / deceleration;

    if (max_time < dt)
    {
        dt = max_time;
    }

    Vector2D new_position = ball_compute_position(ball, dt, deceleration);

    ball->location = new_position;

    Vector2D new_velocity = ball_compute_velocity(ball, dt, deceleration);

    ball->velocity = new_velocity;
}

void ball_collision_adjust_velocity(Ball *ball1, Ball *ball2, float distance)
{
    float dx = ball2->location.x - ball1->location.x;
    float dy = ball2->location.y - ball1->location.y;

    Vector2D normal = (Vector2D){dx / distance, dy / distance};

    Vector2D tangent = (Vector2D){-normal.y, normal.x};

    float tan_dot_v1 = ball1->velocity.x * tangent.x + ball1->velocity.y * tangent.y;
    float tan_dot_v2 = ball2->velocity.x * tangent.x + ball2->velocity.y * tangent.y;

    float normal_dot_v1 = ball1->velocity.x * normal.x + ball1->velocity.y * normal.y;
    float normal_dot_v2 = ball2->velocity.x * normal.x + ball2->velocity.y * normal.y;

    // Conservation of momentum
    float momentum1 = (normal_dot_v1 * (ball1->mass - ball2->mass) + 2.0f * ball2->mass * normal_dot_v2) / (ball1->mass + ball2->mass);
    float momentum2 = (normal_dot_v2 * (ball2->mass - ball1->mass) + 2.0f * ball1->mass * normal_dot_v1) / (ball1->mass + ball2->mass);

    ball1->velocity.x = tangent.x * tan_dot_v1 + normal.x * momentum1;
    ball1->velocity.y = tangent.y * tan_dot_v1 + normal.y * momentum1;

    ball2->velocity.x = tangent.x * tan_dot_v2 + normal.x * momentum2;
    ball2->velocity.y = tangent.y * tan_dot_v2 + normal.y * momentum2;
}

void ball_collision_adjust_positions(Ball *ball1, Ball *ball2, float distance)
{
    float dx = ball2->location.x - ball1->location.x;
    float dy = ball2->location.y - ball1->location.y;

    float overlap = 0.5f * (distance - ball1->radius - ball2->radius);

    float nx = dx / distance;
    float ny = dy / distance;

    ball1->location.x += overlap * nx;
    ball1->location.y += overlap * ny;

    ball2->location.x -= overlap * nx;
    ball2->location.y -= overlap * ny;
}

void ball_adjust_small_velocity(Ball *ball)
{
    if (fabsf(ball->velocity.x) < MOVING_THRESHOLD)
    {
        ball->velocity.x = 0;
    }

    if (fabsf(ball->velocity.y) < MOVING_THRESHOLD)
    {
        ball->velocity.y = 0;
    }
}