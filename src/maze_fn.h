#ifndef MAZE_FN_H
#define MAZE_FN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 640
#define MAP_WIDTH 12
#define MAP_HEIGHT 12
#define FOV 60
#define FOV_SCALE 0.66
#define MAP_SCALE 20
#define SPRITE_SIZE 0.6
#define M_PI 3.14159265358979323846

/* colors */
#define CEILING_COLOR 0x87CEEB      // sky blue
#define FLOOR_COLOR 0x8B4513        // saddle brown
#define WALL_COLOR_NS 0xA0522D      // burnt sienna (for NS walls)
//#define WALL_COLOR_EW 0xCD853F    // peru
#define WALL_COLOR_EW 0x8B0000      // Dark Red (for EW walls)
#define MAP_WALL_COLOR 0x000000  // black
//#define MAP_WALL_COLOR 0xFF0C00     // Red (for map walls)
#define MAP_EMPTY_COLOR 0x0CF0F    // Green (for map floor)
#define MAP_PLAYER_COLOR 0x0000FF   // Blue (for player)
#define MAP_LINE_COLOR 0xFF00FF    // Magenta (for rays)
// #define MAP_LINE_COLOR 0xFFFF00     // Yellow (for player line of sight)
#define TILE_SIZE 1024
#define TEXTURE_WIDTH 1024
#define TEXTURE_HEIGHT 1024
#define MAX_SPRITES 10

typedef struct
{
    double x;
    double y;
    double angle;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} Player;

typedef struct
{
    double x;
    double y;
    double distance;
} sprite;

extern Player player;  // starting point for player
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern SDL_Texture *hedge_texture;
extern SDL_Texture *tree_texture;
extern int map[MAP_WIDTH][MAP_HEIGHT];
extern int running;
extern int show_map;
extern double tree_x;
extern double tree_y;
extern sprite tree_sprites[];
extern int num_sprites;

void draw_vertical_line(SDL_Renderer *renderer, int x, int y1, int y2, int color);
void draw_map(SDL_Renderer *renderer);
void cast_ray(SDL_Renderer *renderer);
void init_window(void);
void load_map(const char *filename);
void destroy_window(void);
int is_colliding(double x, double y);
void process_input(void);
void sort_sprites_by_distance(sprite* sprites, int num_sprites);

#endif /* MAZE_H */
