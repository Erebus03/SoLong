/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:53 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 00:53:34 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*

    my foold_fill logic is prbly wrong 
    i made return a error if it found at least one 0
    i should actually only check if there is a path
				to all the coins and the exit.

*/

void	flood_fill(char **map, int x, int y)
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
	int	j;
	int	error;

	i = 0;
	error = 0;
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
		return (0);
	else
		return (1);
}

int	all_is_reachable(int x, int y, int rows, int cols)
{
	int		fd;
	char	**map_copy;

	fd = open("map.ber", O_RDONLY);
	map_copy = make_map(fd, &rows, &cols);
	flood_fill(map_copy, x, y);
	if (check_reachability(map_copy, &rows, &cols) == 0)
	{
		free_map(map_copy, rows);
		return (0);
	}
	else
		return (1);
}
