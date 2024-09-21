#include "maze_fn.h"
#include "textures.h"
/**
 * cast_ray - Cast a ray from the player's position to et a 3D view.
 * @renderer: The renderer to draw on.
 */
void cast_ray(SDL_Renderer *renderer)
{
    // calculate sprite distances
    for (int i = 0; i < num_sprites; i++)
    {
        tree_sprites[i].distance = ((player.x - tree_sprites[i].x) * (player.x - tree_sprites[i].x) + (player.y - tree_sprites[i].y) * (player.y - tree_sprites[i].y));
    }

    // sort the sprites based on distance, far to close
    sort_sprites_by_distance(tree_sprites, num_sprites);

    double z_buffer[SCREEN_WIDTH];
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        z_buffer[x] = 99999.0;
    }

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double ray_angle = fmod((player.angle - FOV / 2.0) + ((double)x / SCREEN_WIDTH) * FOV, 360.0);
        if (ray_angle < 0)
            ray_angle += 360;

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
            else if (map[testY][testX] == 1)
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

        // fish eye correction
        double corrected_distance = distance * cos((player.angle - ray_angle) * M_PI / 180);
        z_buffer[x] = corrected_distance;

        int ceiling = (SCREEN_HEIGHT / 2) - SCREEN_HEIGHT / 
        (corrected_distance * 2);
        int floor_height = SCREEN_HEIGHT - ceiling;

        draw_vertical_line(renderer, x, 0, ceiling, CEILING_COLOR);
        /* draw_vertical_line(renderer, x, ceiling, floor, wall_orientation ? WALL_COLOR_NS : WALL_COLOR_EW);*/
        draw_vertical_line(renderer, x, floor_height, SCREEN_HEIGHT, FLOOR_COLOR);

        /* claculate texture x offset */
        double wall_hitX;

        if (wall_orientation == 1)
        {
            /* use y for EW walls */
            wall_hitX = player.y + rayY * distance;
        }
        else
        {
            /* x for NS walls */
            wall_hitX = player.x + rayX *distance;
        }
        /* keep only the fractional part */
        wall_hitX -= floor(wall_hitX);

        /* get correct x - coo on texture */
        int textureX = (int)(wall_hitX * TEXTURE_WIDTH);

        SDL_Rect src_rect = {textureX, 0, 1, TEXTURE_HEIGHT};
        SDL_Rect dest_rect = {x, ceiling, 1, floor_height - ceiling};
        SDL_RenderCopy(renderer, hedge_texture, &src_rect, &dest_rect);

        /* render sprites */
        for (int i = 0; i < num_sprites; i++)
        {
            double spriteX = tree_sprites[i].x - player.x;
            double spriteY = tree_sprites[i].y - player.y;

            double inv_det = 1.0 / (player.plane_x * player.dir_y - player.dir_x * player.plane_y);
            double transformX = inv_det * (player.dir_y * spriteX - player.dir_x * spriteY);
            double transformY = inv_det * (-player.plane_y * spriteX + player.plane_x * spriteY);

            int sprite_screenX = (int)((SCREEN_WIDTH / 2) * (1 + transformX / transformY));

            // calculate dimensions of sprite on screen
            int sprite_height = abs((int)(SCREEN_HEIGHT / transformY)) * SPRITE_SIZE;
            int sprite_width = abs((int)(SCREEN_HEIGHT / transformY)) * SPRITE_SIZE;

            // calculate drawing bounds
            int draw_startY = -sprite_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_startY < 0)
                draw_startY = 0;
            int draw_endY = sprite_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_endY >= SCREEN_HEIGHT)
                draw_endY = SCREEN_HEIGHT - 1;
            
            int draw_startX = -sprite_width / 2 + sprite_screenX;
            if (draw_startX < 0)
                draw_startX = 0;
            int draw_endX = sprite_width / 2 + sprite_screenX;
            if (draw_endX >= SCREEN_WIDTH)
                draw_endX = SCREEN_WIDTH - 1;

            // render sprite if within screen bounds
            for (int stripe = draw_startX; stripe < draw_endX; stripe++)
            {
                if (transformY > 0 && stripe > 0 && stripe < SCREEN_WIDTH && transformY < z_buffer[stripe])
                {
                    int texX = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screenX)) * TEXTURE_WIDTH / sprite_width) / 256;

                    SDL_Rect sprite_src_rect = {texX, 0, 1, TEXTURE_HEIGHT};
                    SDL_Rect sprite_dest_rect = {stripe, draw_startY, 1, draw_endY - draw_startY};
                    SDL_RenderCopy(renderer, tree_texture, &sprite_src_rect, &sprite_dest_rect);
                }
            }
        }
    }
}

/**
 * sort sprites by distance
 */
void sort_sprites_by_distance(sprite* sprites, int num_sprites)
{
    for (int i = 0; i < num_sprites - 1; i++)
    {
        for (int j = 0; j < num_sprites - i - 1; j++)
        {
            if (sprites[j].distance < sprites[j + 1].distance)
            {
                sprite temp = sprites[j];
                sprites[j] = sprites[j + 1];
                sprites[j + 1] = temp;
            }
        }
    }
}
