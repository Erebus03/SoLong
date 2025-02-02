/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:53 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 21:16:02 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <fcntl.h>

int	check_reachability(char **map, int *rows, int *cols)
{
	int	i;
	int	j;
	int	return_value;

	i = 0;
	return_value = 1;
	while (i < *rows)
	{
		j = 0;
		while (j < *cols)
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
			{
				ft_printf("Position(%d, %d) is not reachable\n", i, j);
				return_value = 0;
			}
			j++;
		}
		i++;
	}
	return (return_value);
}

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

int	all_is_reachable(int x, int y, int rows, int cols)
{
	int		fd;
	char	**map_copy;
	int		ret;

	fd = open("map.ber", O_RDONLY);
	map_copy = make_map(fd, &rows, &cols);
	flood_fill(map_copy, x, y);
	ret = check_reachability(map_copy, &rows, &cols);
	free_map(map_copy, rows);
	return (ret);
}
