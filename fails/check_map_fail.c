#include "minilibx-linux/mlx.h"
#include "solong.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int validate_map_size(int fd) 
{
    char *line;

    line = get_next_line(fd);

    int i = 0;
    int first_line_len = strlen(line);
    while (line) {
        if (strlen(line) != first_line_len)
            return -1;
        i++;
        free(line);
        line = get_next_line(fd);
    }
    
}

int map_is_valid(int fd)
{
    Map *map;
    char *line;

    map = malloc(sizeof(Map));

    validate_map_size(fd);
    line = get_next_line(fd);
    // map->width = strlen(line);

    int i = 0;
    int first_line_len = strlen(line);
    while (line) {
        if (strlen(line) != first_line_len)
        {
            printf("bchi mak sgidi l3bar\n");
            return 1;
        }
        printf("line[%d] >%s< with lenght >%d<\n", i, line, strlen(line));
        i++;
        free(line);
        line = get_next_line(fd);
    }

    printf ("map.height %d | map.width %d\n", i, map->width);
    return 0;
}


int main() {
    int fd = open("map.ber", O_RDONLY);

    printf("is map valid? =>>%d<\n", map_is_valid(fd));

    return 0;
}
    

//     char *line = get_next_line(fd);

//     int i = 0;
//     while (line[i]) {
//         printf(">%d<\n", line[i]);
//         i++;
//     }
// }
/*
    Map *map = malloc(sizeof(Map));
    map->width = strlen(map_str) / MAX_MAP_SIZE;
    map->height = MAX_MAP_SIZE;

    // Convert string to 2D grid
    for (int y = 0; y < MAX_MAP_SIZE; y++) {
        for (int x = 0; x < map->width; x++) {
            map->grid[y][x] = map_str[y * map->width + x];
        }
    }

    // Validate map
    if (!validate_map(map)) {
        free(map);
        return NULL;
    }

    return map;
}
*/

/*
bool validate_map(Map *map) {
    int coins = 0, players = 0, exits = 0;

    // Check map rows and count elements
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            // Count game elements
            if (map->grid[y][x] == 'C') coins++;
            if (map->grid[y][x] == 'P') players++;
            if (map->grid[y][x] == 'E') exits++;

            // Check first/last row and column are walls
            if ((y == 0 || y == map->height-1 || x == 0 || x == map->width-1)
                && map->grid[y][x] != '1') {
                return false;
            }
        }
    }

    // Validate game elements
    return (coins > 0 && players == 1 && exits == 1);
}
*/
