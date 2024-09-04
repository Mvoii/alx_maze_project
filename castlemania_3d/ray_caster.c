#include "maze_fn.h"
/**
 * cast_ray - Cast a ray from the player's position to et a 3D view.
 * @renderer: The renderer to draw on.
 */
void cast_ray(SDL_Renderer *renderer)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double ray_angle = (player.angle - FOV / 2.0) + ((double)x / SCREEN_WIDTH) * FOV;

        double rayX = cos(ray_angle * M_PI / 180);
        double rayY = sin(ray_angle * M_PI / 180);

        double distance = 0;
        int hit_wall = 0;
        int wall_orientation = 0;   // 0 for NS: 1 for EW

        while (!hit_wall && distance < 16)
        {
            distance += 0.1;

            int testX = (int)(player.x + rayX * distance);
            int testY = (int)(player.y + rayY * distance);

            if (testX < 0 || testX >= MAP_WIDTH || testY < 0 || testY >= MAP_HEIGHT)
            {
                hit_wall = 1;
                distance = 16;
            }
            else if (map[testX][testY] == 1)
            {
                hit_wall = 1;

                /* determine wall orientation */
                double block_midX = testX + 0.5;
                double block_midY = testY + 0.5;
                double test_pointX = player.x + rayX * distance;
                double test_pointY = player.y + rayY * distance;
                double test_angle = atan2(test_pointY - block_midY, test_pointX - block_midX);

                if (test_angle > -M_PI * 0.25 && test_angle < M_PI * 0.25)
                    wall_orientation = 1;
                else if (test_angle > M_PI * 0.25 && test_angle < M_PI * 0.75)
                    wall_orientation = 0;
                else if (test_angle > -M_PI * 0.75 && test_angle < -M_PI * 0.25)
                    wall_orientation = 0;
                else
                    wall_orientation = 1;
            }
        }

        int ceiling = (SCREEN_HEIGHT / 2) - SCREEN_HEIGHT / distance;
        int floor = SCREEN_HEIGHT - ceiling;

        draw_vertical_line(renderer, x, 0, ceiling, CEILING_COLOR);
        draw_vertical_line(renderer, x, ceiling, floor, wall_orientation ? WALL_COLOR_NS : WALL_COLOR_EW);
        draw_vertical_line(renderer, x, floor, SCREEN_HEIGHT, FLOOR_COLOR);
    }
}
