#include "header.h"

// #include <SDL2/SDL.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
// #define MAP_WIDTH 24
// #define MAP_HEIGHT 24
// #define FOV 60

// define colours
// #define CEILING_COLOUR 0x87CEEB      // sky blue
// #define FLOOR_COLOUR 0x8B4513        // saddle brown
// #define WALL_COLOUR_NS 0xA0522D         // burnt sienna
// #define WALL_COLOUR_EW 0xCD853F         // peru

int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,1,1,1,0,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,0,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

// typedef struct
// {
//     double x;
//     double y;
//     double angle;
// } Player;

Player player = { 4, 4, 0};

int running = 1;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

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
        int wallOrientation = 0;

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

                // determine wall orientation
                double blockMidX = testX + 0.5;
                double blockMidY = testY + 0.5;
                double testPointX = player.x + rayX * distance;
                double testPointY = player.y + rayY * distance;
                double testAngle = atan2(testPointY - blockMidY, testPointX - blockMidX);

                if (testAngle > -M_PI * 0.25 && testAngle < M_PI * 0.25)
                    wallOrientation = 1;
                else if (testAngle > M_PI * 0.25 && testAngle < M_PI * 0.75)
                    wallOrientation = 0;
                else if (testAngle > -M_PI * 0.75 && testAngle < -M_PI * 0.25)
                    wallOrientation = 0;
                else
                    wallOrientation = 1;
            }
        }

        int ceiling = (SCREEN_HEIGHT / 2) - SCREEN_HEIGHT / distance;
        int floor = SCREEN_HEIGHT - ceiling;

        drawVerticalLine(renderer, x, 0, ceiling, CEILING_COLOUR);
        drawVerticalLine(renderer, x, ceiling, floor, wallOrientation ? WALL_COLOUR_NS : WALL_COLOUR_EW);
        drawVerticalLine(renderer, x, floor, SCREEN_HEIGHT, FLOOR_COLOUR);
    }
}

void init_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Unable to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    switch (event.type)
    {
        case SDL_QUIT:
            running = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    running = 0;
                    break;
                
                case SDLK_LEFT:
                    player.angle -= 5;  // left by 5 degrees
                    if (player.angle < 0)
                        player.angle += 360;    // ensure angle stays within the 0-360 range
                    break;

                case SDLK_RIGHT:
                    player.angle += 5;  // right by 5 degrees
                    if (player.angle >= 360)
                        player.angle -= 360;    // ensure angle stays within the 0-360 range
                    break;
                default:
                    break;
            }
            break;

        case SDL_MOUSEMOTION:
            player.angle += event.motion.xrel * 0.1;  // adjust sensitivity by changing multiplier
            if (player.angle < 0)
                player.angle += 360;
            if (player.angle >= 360)
                player.angle -= 360;

            break;
        
        default:
            break;
    }
    // continuous movement
    if (state[SDL_SCANCODE_W])
    {
        player.x += cos(player.angle * M_PI / 180) * 0.1;
        player.y += sin(player.angle * M_PI / 180) * 0.1;
    }
    if (state[SDL_SCANCODE_S])  // Move backward
    {
        player.x -= cos(player.angle * M_PI / 180) * 0.1;
        player.y -= sin(player.angle * M_PI / 180) * 0.1;
    }
    if (state[SDL_SCANCODE_A])  // Strafe left
    {
        player.x += cos((player.angle - 90) * M_PI / 180) * 0.1;
        player.y += sin((player.angle - 90) * M_PI / 180) * 0.1;
    }
    if (state[SDL_SCANCODE_D])  // Strafe right
    {
        player.x += cos((player.angle + 90) * M_PI / 180) * 0.1;
        player.y += sin((player.angle + 90) * M_PI / 180) * 0.1;
    }
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    /* SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); */

    init_window();

    while (running)
    {
        process_input();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        castRays(renderer);

        SDL_RenderPresent(renderer);
    }
    destroy_window();

    return (0);
}
