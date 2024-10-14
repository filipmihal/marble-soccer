#include <SDL.h>
#include "ball.h"

static void draw_circle(SDL_Renderer *renderer, int x0, int y0, int radius)
{
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void render(SDL_Renderer *renderer, Ball *team1, Ball *team2, Ball *ball, short num_players)
{
    // Clear the screen with a background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Set the color for the balls
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // White color for balls

    // Draw each ball as a circle
    for (int i = 0; i < num_players; ++i)
    {
        draw_circle(renderer, (int)team1[i].location.x, (int)team1[i].location.y, (int)team1[i].radius);
    }

    // Set the color for the balls
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // White color for balls

    // Draw each ball as a circle
    for (int i = 0; i < num_players; ++i)
    {
        draw_circle(renderer, (int)team2[i].location.x, (int)team2[i].location.y, (int)team2[i].radius);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for balls

    draw_circle(renderer, (int)ball->location.x, (int)ball->location.y, (int)ball->radius);

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}
