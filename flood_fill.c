#include "solong.h"

/*

    my foold_fill logic is prbly wrong 
    i made return a error if it found at least one 0
    i should actually only check if there is a path to all the coins and the exit.

*/

void    flood_fill(char **map, int x, int y) //make size dynamic
{
    if (x < 0 || x >= 10 || y < 0 || y >= 5)
        return ;
    if (map[y][x] == '1' || map[y][x] == 'V')
        return ;

    map[y][x] = 'V';
    
    flood_fill(map, x - 1, y);
    flood_fill(map, x + 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}

int	check_reachability(char **map, int *rows, int *cols)
{
	int	i;
	int j;
	int error;

	i = 0;
	error = 0;
	printf("checking reach now..\n");
	printf("rows=%d | cols=%d\n", *rows, *cols);
	while (i < *rows)
	{
		j = 0;
		while (j < *cols)
		{
			if (map[i][j] == 'C')
			{
				printf("item(%d, %d) is not reachable\n", i, j);
				error = 1;
			}
			else if (map[i][j] == 'E')
			{
				printf("exit(%d, %d) is not reachable\n", i, j);
				error = 1;
			}
			j++;
		}
		i++;
	}
	if (error == 1)
		return 0;
	else
		return 1;
}

int	all_is_reachable(int x, int y, int rows, int cols)
{
	int fd;
	char **map_copy;

	fd = open("map.ber", O_RDONLY);
	printf("opened fd==%d\n", fd);
	map_copy = make_map(fd, &rows, &cols);
	printf("other map made:\n");

    for (int i = 0; i < rows; i++) {
        printf("%s\n", map_copy[i]); // Print each row as a string
    }

	flood_fill(map_copy, x, y);

	printf("o_map after fooldfill\n");
    for (int i = 0; i < rows; i++) {
        printf("%s\n", map_copy[i]); // Print each row as a string
    }

	printf("rows=%d | cols=%d\n", rows, cols);
	if (check_reachability(map_copy, &rows, &cols) == 0)
	{
		free_map(map_copy, rows);
		return 0;
	}
	else
		return 1;
}