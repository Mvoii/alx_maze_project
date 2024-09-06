#include "maze_fn.h"

/**
 * draw_vertical_line - Draw a vertical line on the screen.
 * @renderer: The renderer to draw on.
 * @x: The x coordinate of the line.
 * @y1: The starting y coordinate of the line.
 * @y2: The ending y coordinate of the line.
 * @color: The color of the line.
 */
void draw_vertical_line(SDL_Renderer *renderer, int x, int y1, int y2, int color)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawLine(renderer, x, y1, x, y2);
}

/**
 * draw_map - Draw the map on the screen and player line of sight.
 * @renderer: The renderer to draw on.
 */
void draw_map(SDL_Renderer *renderer)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int color = map[x][y] == 1 ? MAP_WALL_COLOR : MAP_EMPTY_COLOR;
            SDL_Rect rect = {x * MAP_SCALE, y * MAP_SCALE, MAP_SCALE, MAP_SCALE};
            SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 200); // 200 - opaqueness
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    /* Draw the player line of sight */
    double sight_x = player.x + cos(player.angle * M_PI / 180) * 5; // extend line by 5 units
    double sight_y = player.y + sin(player.angle * M_PI / 180) * 5; // extend line by 5 units
    int screen_x = player.x * MAP_SCALE + MAP_SCALE / 2;
    int screen_y = player.y * MAP_SCALE + MAP_SCALE / 2;
    int sight_end_x = sight_x * MAP_SCALE + MAP_SCALE / 2;
    int sight_end_y = sight_y * MAP_SCALE + MAP_SCALE / 2;

    SDL_SetRenderDrawColor(renderer, (MAP_LINE_COLOR >> 16) & 0xFF, (MAP_LINE_COLOR >> 8) & 0xFF, MAP_LINE_COLOR & 0xFF, 255);
    SDL_RenderDrawLine(renderer, screen_x, screen_y, sight_end_x, sight_end_y);
}
