#include "maze_fn.h"
/**
 * load_map - loads the map from a file.
 * @filename: The name of the file to load.
 */

int num_sprites = 0;
sprite tree_sprites[MAX_SPRITES];

void load_map(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Unable to open file: %s\n", filename);
        exit(1);
    }

    char buffer[256];
    int y = 0;
    //double tree_x = 0;
    //double tree_y = 0;

    while (fgets(buffer, sizeof(buffer), file) && y < MAP_HEIGHT)
    {
        for (int x = 0; x < MAP_WIDTH && buffer[x] != '\0'; x++)
        {

            switch (buffer[x])
            {
                case '#':
                    map[y][x] = 1;
                    break;

                case 'T':
                    map[y][x] = 0;  // sprite as empty space
                    if (num_sprites < MAX_SPRITES)
                    {
                        tree_sprites[num_sprites].x = x + 0.5; // centre of the block
                        tree_sprites[num_sprites].y = y + 0.5;
                        num_sprites++;
                    }
                    break;

                case 'P':
                    map[y][x] = 0;
                    player.x = x + 0.5;
                    player.y = y + 0.5;
                    player.angle = 0;
                    player.dir_x = cos(player.angle * M_PI / 180);
                    player.dir_y = sin(player.angle * M_PI / 180);
                    player.plane_x = -player.dir_y * FOV_SCALE;
                    player.plane_y = player.dir_x * FOV_SCALE;
                    break;

                default:
                    map[y][x] = 0;
                    break;
            }            
        }
        y++;
    }

    fclose(file);

    printf("map loaded\n Player start: x=%f, y=%f\n", player.x, player.y);
    printf("num_sprites: %d\n", num_sprites);
}
