#include "maze_fn.h"
/**
 * is_colliding - Check if givern pos collides with a wall.
 * @x: X coordinates to chack
 * @y: Y coordinates to check
 * 
 * Return: 1 if collides, 0 otherwise.
 */
int is_colliding(double x, double y)
{
    int mapX = (int)x;
    int mapY = (int)y;

    /* check map boundaries */
    if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
    {
        return (1);
    }
    return (0);
}
