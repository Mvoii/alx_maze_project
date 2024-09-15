#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void load_textures(SDL_Renderer *renderer);
void free_textures();
void render_textures(SDL_Renderer *renderer);

#endif /* TEXTURES_H */
