#include "maze.h"
#include "textures.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

// Declare texture variables
SDL_Texture* hedgeTexture = NULL;
SDL_Texture* treeTexture = NULL;

// Load textures from file
void loadTextures(SDL_Renderer* renderer) {
    hedgeTexture = IMG_LoadTexture(renderer, "hedge.png");
    if (!hedgeTexture) {
        printf("Error loading hedge texture: %s\n", SDL_GetError());
        exit(1);
    }

    treeTexture = IMG_LoadTexture(renderer, "tree.png");
    if (!treeTexture) {
        printf("Error loading tree texture: %s\n", SDL_GetError());
        exit(1);
    }
}

// Free textures when done
void freeTextures() {
    if (hedgeTexture) SDL_DestroyTexture(hedgeTexture);
    if (treeTexture) SDL_DestroyTexture(treeTexture);
}


// void renderTextures(SDL_Renderer* renderer) {
//     for (int y = 0; y < MAP_HEIGHT; y++) {
//         for (int x = 0; x < MAP_WIDTH; x++) {
//             if (map[y][x] == 1) { // Assuming '1' is a wall
//                 SDL_Rect wallRect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
//                 SDL_RenderCopy(renderer, hedgeTexture, NULL, &wallRect);
//             }
//         }
//     }
// 
//     // Render the tree at the center of the map
//     SDL_Rect treeRect = {5 * TILE_SIZE, 5 * TILE_SIZE, TILE_SIZE, TILE_SIZE * 2}; // Adjust as necessary
//     SDL_RenderCopy(renderer, treeTexture, NULL, &treeRect);
// }
