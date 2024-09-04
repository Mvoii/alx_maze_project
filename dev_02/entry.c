#include "maze.h"

int map[MAP_HEIGHT][MAP_WIDTH];     //defined only here
int running = 1;
int show_map = 1;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Player player = {2, 2, 0};

/**
 * main - Entry point of the game.
 * @argc: num of CLI args.
 * @argv: array of CLI args.
 * 
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <mapfile>\n", argv[0]);
        return 1;
    }

    init_window();
    load_map(argv[1]);

    while (running)
    {
        process_input();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        cast_ray(renderer);

        if (show_map)
        {
            draw_map(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    destroy_window();
    return (0);
}
