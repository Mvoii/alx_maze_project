#include "textures.h"
#include "maze_fn.h"

// TODO: documet the functions

SDL_Texture *hedge_texture = NULL;
SDL_Texture *tree_texture = NULL;

void load_textures(SDL_Renderer *renderer)
{
  hedge_texture = IMG_LoadTexture(renderer, "hedge.png");

  if (!hedge_texture)
  {
    printf("Error loading hedge texture: %s\n", SDL_GetError());
    exit(1);
  }

  tree_texture = IMG_LoadTexture(renderer, "tree.png");

  if (!tree_texture)
  {
    printf("Error loading tree texture: %s\n", SDL_GetError());
    exit(1);
  }
}

void free_textures()
{
  if (hedge_texture)
  {
    SDL_DestroyTexture(hedge_texture);
  }

  if (tree_texture)
  {
    SDL_DestroyTexture(tree_texture);
  }
}
