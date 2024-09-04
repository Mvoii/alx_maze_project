#include "maze.h"
/**
 * process_input - Process the user input.
 */
void process_input(void)
{
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
                    {
                        /* ensure that angle stays within 0 - 360 degrees */
                        player.angle += 360;
                    }
                    break;
                
                case SDLK_RIGHT:
                    player.angle += 5;  // right by 5 degrees
                    if (player.angle >= 360)
                    {
                        /* ensure angle stays within 0 -360 degrees */
                        player.angle -= 360;
                    }
                    break;
                
                case SDLK_m:
                    show_map = !show_map;
                    break;
                
                default:
                    break;
            }
            break;

        case SDL_MOUSEMOTION:
            player.angle += event.motion.xrel * 0.1;    // adjust speed by changing the 0.1
            if (player.angle < 0)
            {
                /* within 0 - 360 degrees */
                player.angle += 360;
            }
            if (player.angle >= 360)
            {
                /* stay within 0 - 360 degrees*/
                player.angle -= 360;
            }
            break;
        
        default:
            break;
    }

    /* player next potential position */
    double move_step = 0.1;
    double next_x = player.x;
    double next_y = player.y;

    /* continuous movements */
    if (state[SDL_SCANCODE_W])
    {
        next_x += cos(player.angle * M_PI / 180) * move_step;
        next_y -= sin(player.angle * M_PI / 180) * move_step;
    }

    if (state[SDL_SCANCODE_S])
    {
        next_x -= cos(player.angle * M_PI / 180) * move_step;
        next_y -= sin(player.angle * M_PI / 180) * move_step;
    }

    if (state[SDL_SCANCODE_A])  // strafe left
    {
        next_x += cos((player.angle - 90) * M_PI / 180) * move_step;
        next_y += sin((player.angle - 90) * M_PI / 180) * move_step;
    }

    if (state[SDL_SCANCODE_D])  // strafe right
    {
        next_x += cos((player.angle + 90) * M_PI / 180) * move_step;
        next_y += sin((player.angle + 90) * M_PI / 180) * move_step;
    }

    /* collision detection */
    int colliding_x = is_colliding(next_x, player.y);
    int colliding_y = is_colliding(player.x, next_y);
    int colliding_both = is_colliding(next_x, next_y);

    if (!colliding_both)
    {
        if (!colliding_x)
        {
            player.x = next_x;  // move along x
        }
        if (!colliding_y)
        {
            player.y = next_y;  // move along y
        }
    }
}
