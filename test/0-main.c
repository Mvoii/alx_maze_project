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
