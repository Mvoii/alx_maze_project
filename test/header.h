#ifndef HEADER_H
#define HEADER_H

#include <math.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define FOV 60

// define colours
#define CEILING_COLOUR 0x87CEEB      // sky blue
#define FLOOR_COLOUR 0x8B4513        // saddle brown
#define WALL_COLOUR 0xA0522D         // burnt sienna

#define WALL_COLOUR_NS 0xA0522D         // burnt sienna
#define WALL_COLOUR_EW 0xCD853F         // peru

// player
typedef struct
{
    double x;
    double y;
    double angle;
} Player;

#endif
