#include "solong.h"

/*

    my foold_fill logic is prbly wrong 
    i made return a error if it found at least one 0
    i should actually only check if there is a path to all the coins and the exit.

*/

void    flood_fill(char map[5][11], int x, int y)
{
    if (x < 0 || x >= 10 || y < 0 || y >= 5)
        return ;
    if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'C' || map[y][x] == 'E')
        return ;

    map[y][x] = 'V';
    
    flood_fill(map, x - 1, y);
    flood_fill(map, x + 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}

int	all_is_reachable(int x, int y, int rows, int cols)
{
	int fd;
	char **map;

	fd = open("map.ber", O_RDONLY);
	map = make_map(fd, &rows, &cols);
	flood_fill(map, x, y);
}