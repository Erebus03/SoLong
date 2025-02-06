/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:53 by araji             #+#    #+#             */
/*   Updated: 2025/02/04 06:32:08 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_reachability(char **map, t_map *grid)
{
	int	i;
	int	j;
	int	return_value;

	i = 0;
	return_value = 1;
	while (i < grid->rows)
	{
		j = 0;
		while (j < grid->cols)
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
			{
				printf("\nPosition(%d, %d)[%c] is not reachable\n",
					i, j, map[i][j]);
				return_value = 0;
			}
			j++;
		}
		i++;
	}
	return (return_value);
}

void	flood_fill(t_map *grid, char **map, int x, int y)
{
	if (x < 0 || x >= grid->cols || y < 0 || y >= grid->rows)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(grid, map, x - 1, y);
	flood_fill(grid, map, x + 1, y);
	flood_fill(grid, map, x, y + 1);
	flood_fill(grid, map, x, y - 1);
}

int	all_is_reachable(int x, int y, t_map *grid, char *filename)
{
	int		fd;
	char	**map_copy;
	int		ret;

	fd = open(filename, O_RDONLY);
	map_copy = make_map(fd, grid, filename);
	flood_fill(grid, map_copy, x, y);
	for (int i = 0; i < grid->rows; i++)
		printf("%s\n", map_copy[i]);
	ret = check_reachability(map_copy, grid);
	free_map(map_copy, grid->rows);
	return (ret);
}
