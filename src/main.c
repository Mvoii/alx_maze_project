#include "maze_fn.h"
#include "textures.h"

int map[MAP_WIDTH][MAP_HEIGHT];
int running = 1;
int show_map = 1;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Player player;

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
    printf("\tgame  starting\n \n \tmap %s\n", argv[1]);
    init_window();
    load_map(argv[1]);

    for (int i = 0; i < num_sprites; i++)
    {
        printf("sprite %d: x=%f, y=%f\n", i, tree_sprites[i].x, tree_sprites[i].y);
    }
    printf("\n player x=%f, y=%f\n", player.x, player.y);

    load_textures(renderer);

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

    printf("\n\tgame  ending\n");
    return (0);
}
