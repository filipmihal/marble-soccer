#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <stdbool.h>

#include "playground.h"
#include "ball.h"

void simulate(Ball *balls[], Playground *playground, int num_balls, float dt);

bool is_simulation_idle(Ball *balls[], int num_balls);

#endif