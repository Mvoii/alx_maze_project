#include "maze.h"
/**
 * load_map - loads the map from a file.
 * @filename: The name of the file to load.
 */
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

    while (fgets(buffer, sizeof(buffer), file) && y < MAP_HEIGHT)
    {
        for (int x = 0; x < MAP_WIDTH && buffer[x] != '\0'; x++)
        {
            map[y][x] = buffer[x] == '1' ? 1 : 0;
        }
        y++;
    }

    fclose(file);
}
