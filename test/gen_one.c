#include <SDL2/SDL.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define FOV 60

// Define colors
#define CEILING_COLOR 0x87CEEB  // Sky blue
#define FLOOR_COLOR 0x8B4513    // Saddle brown
#define WALL_COLOR_NS 0xA0522D  // Sienna (for North/South facing walls)
#define WALL_COLOR_EW 0x8B0000  // Dark Red (for East/West facing walls)

int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,0,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

typedef struct {
    double x;
    double y;
    double angle;
} Player;

Player player = {4, 4, 0};  // Start in the middle of the map

int running = 1;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void drawVerticalLine(SDL_Renderer* renderer, int x, int y1, int y2, int color) {
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawLine(renderer, x, y1, x, y2);
}

void castRays(SDL_Renderer* renderer) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double rayAngle = (player.angle - FOV / 2.0) + ((double)x / SCREEN_WIDTH) * FOV;
        
        double rayX = cos(rayAngle * M_PI / 180);
        double rayY = sin(rayAngle * M_PI / 180);
        
        double distance = 0;
        int hitWall = 0;
        int wallOrientation = 0;  // 0 for NS, 1 for EW
        
        while (!hitWall && distance < 16) {
            distance += 0.1;
            
            int testX = (int)(player.x + rayX * distance);
            int testY = (int)(player.y + rayY * distance);
            
            if (testX < 0 || testX >= MAP_WIDTH || testY < 0 || testY >= MAP_HEIGHT) {
                hitWall = 1;
                distance = 16;
            } else if (map[testY][testX] == 1) {
                hitWall = 1;
                
                // Determine wall orientation
                double blockMidX = testX + 0.5;
                double blockMidY = testY + 0.5;
                double testPointX = player.x + rayX * distance;
                double testPointY = player.y + rayY * distance;
                double testAngle = atan2(testPointY - blockMidY, testPointX - blockMidX);
                
                if (testAngle > -M_PI * 0.25 && testAngle < M_PI * 0.25) wallOrientation = 1;
                else if (testAngle > M_PI * 0.25 && testAngle < M_PI * 0.75) wallOrientation = 0;
                else if (testAngle > -M_PI * 0.75 && testAngle < -M_PI * 0.25) wallOrientation = 0;
                else wallOrientation = 1;
            }
        }
        
        int ceiling = (SCREEN_HEIGHT / 2.0) - SCREEN_HEIGHT / distance;
        int floor = SCREEN_HEIGHT - ceiling;
        
        drawVerticalLine(renderer, x, 0, ceiling, CEILING_COLOR);
        drawVerticalLine(renderer, x, ceiling, floor, wallOrientation ? WALL_COLOR_EW : WALL_COLOR_NS);
        drawVerticalLine(renderer, x, floor, SCREEN_HEIGHT, FLOOR_COLOR);
    }
}

void init_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

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
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);
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
                        player.angle += 360;    // ensure angle stays within the 0-360 range
                    break;

                case SDLK_RIGHT:
                    player.angle += 5;  // right by 5 degrees
                    if (player.angle >= 360)
                        player.angle -= 360;    // ensure angle stays within the 0-360 range
                    break;
                default:
                    break;
            }
            break;

        case SDL_MOUSEMOTION:
            player.angle += event.motion.xrel * 0.1;  // adjust sensitivity by changing multiplier
            if (player.angle < 0)
                player.angle += 360;
            if (player.angle >= 360)
                player.angle -= 360;
            break;
        
        default:
            break;
    }
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    init_window();

    while (running) {
        process_input();
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        castRays(renderer);
        
        SDL_RenderPresent(renderer);
    }
    destroy_window();
    
    return 0;
}
