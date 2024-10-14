#ifndef RENDER_H_
#define RENDER_H_

#include <SDL.h>
#include "ball.h"

void render(SDL_Renderer *renderer, Ball *team1, Ball *team2, Ball *ball, short num_players);

#endif