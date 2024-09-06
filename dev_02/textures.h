#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>

// texture functions
//void load_render_texture(SDL_Renderer *renderer, int player_x, int 
//player_y);
//void render_hedge(SDL_Renderer *renderer, SDL_Texture *hedge_texture, 
//int x, int y, int width, int height);
//SDL_Texture *load_texture(const char *file_path, SDL_Renderer *renderer);

// Function declarations
void loadTextures(SDL_Renderer* renderer);
void freeTextures();
void renderTextures(SDL_Renderer* renderer);

#endif /* TEXTURES_H */
