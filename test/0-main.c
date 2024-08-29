#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define FOV 60

// define colours
#define CEILING_COLOUR 0x87CEEB      // sky blue
#define FLOOR_COLOUR 0x8B4513        // saddle brown
#define WALL_COLOUR 0xA0522D         // burnt sienna

int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,0,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

typedef struct
{
    double x;
    double y;
    double angle;
} Player;

Player player = { 3, 4, 0};

void drawVerticalLine(SDL_Renderer *renderer, int x, int y1, int y2, int color)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawLine(renderer, x, y1, x, y2);
}

void castRays(SDL_Renderer *renderer)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double rayAngle = (player.angle - FOV / 2.0) + ((double)x / SCREEN_WIDTH) * FOV;

        double rayX = cos(rayAngle * M_PI / 180);
        double rayY = sin(rayAngle * M_PI / 180);

        double distance = 0;
        int hitWall = 0;

        while (!hitWall && distance < 16)
        {
            distance += 0.1;

            int testX = (int)(player.x + rayX * distance);
            int testY = (int)(player.y + rayY * distance);

            if (testX < 0 || testX >= MAP_WIDTH || testY < 0 || testY >= MAP_HEIGHT)
            {
                hitWall = 1;
                distance = 16;
            }
            else if (map[testX][testY] == 1)
            {
                hitWall = 1;
            }
        }

        int ceiling = (SCREEN_HEIGHT / 2) - SCREEN_HEIGHT / distance;
        int floor = SCREEN_HEIGHT - ceiling;

        drawVerticalLine(renderer, x, 0, ceiling, CEILING_COLOUR);
        drawVerticalLine(renderer, x, ceiling, floor, WALL_COLOUR);
        drawVerticalLine(renderer, x, floor, SCREEN_HEIGHT, FLOOR_COLOUR);
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        castRays(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return (0);
}
