#include "maze_fn.h"
#include "textures.h"

/**
 * init_window - Initialize the SDL window and renderer.
 */
void init_window(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!window)
    {
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        fprintf(stderr, "Unable to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    // Enable linear filtering for textures
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        fprintf(stderr, "Warning: Linear texture filtering not enabled!\n");
        exit(1);
    }

}

/**
 * destroy_window - Destroy the SDL window and renderer.
 */
void destroy_window(void)
{
    /* SDL_DestroyRenderer(renderer); */
    free_textures();
    SDL_DestroyWindow(window);
    SDL_Quit();
}
